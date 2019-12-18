#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mbox_test_device {int /*<<< orphan*/  waitq; void* rx_buffer; void* rx_channel; int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev; void* tx_channel; int /*<<< orphan*/ * tx_mmio; int /*<<< orphan*/ * rx_mmio; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MBOX_MAX_MSG_LEN ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int mbox_test_add_debugfs (struct platform_device*,struct mbox_test_device*) ; 
 void* mbox_test_request_channel (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mbox_test_device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mbox_test_probe(struct platform_device *pdev)
{
	struct mbox_test_device *tdev;
	struct resource *res;
	resource_size_t size;
	int ret;

	tdev = devm_kzalloc(&pdev->dev, sizeof(*tdev), GFP_KERNEL);
	if (!tdev)
		return -ENOMEM;

	/* It's okay for MMIO to be NULL */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	tdev->tx_mmio = devm_ioremap_resource(&pdev->dev, res);
	if (PTR_ERR(tdev->tx_mmio) == -EBUSY) {
		/* if reserved area in SRAM, try just ioremap */
		size = resource_size(res);
		tdev->tx_mmio = devm_ioremap(&pdev->dev, res->start, size);
	} else if (IS_ERR(tdev->tx_mmio)) {
		tdev->tx_mmio = NULL;
	}

	/* If specified, second reg entry is Rx MMIO */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	tdev->rx_mmio = devm_ioremap_resource(&pdev->dev, res);
	if (PTR_ERR(tdev->rx_mmio) == -EBUSY) {
		size = resource_size(res);
		tdev->rx_mmio = devm_ioremap(&pdev->dev, res->start, size);
	} else if (IS_ERR(tdev->rx_mmio)) {
		tdev->rx_mmio = tdev->tx_mmio;
	}

	tdev->tx_channel = mbox_test_request_channel(pdev, "tx");
	tdev->rx_channel = mbox_test_request_channel(pdev, "rx");

	if (!tdev->tx_channel && !tdev->rx_channel)
		return -EPROBE_DEFER;

	/* If Rx is not specified but has Rx MMIO, then Rx = Tx */
	if (!tdev->rx_channel && (tdev->rx_mmio != tdev->tx_mmio))
		tdev->rx_channel = tdev->tx_channel;

	tdev->dev = &pdev->dev;
	platform_set_drvdata(pdev, tdev);

	spin_lock_init(&tdev->lock);

	if (tdev->rx_channel) {
		tdev->rx_buffer = devm_kzalloc(&pdev->dev,
					       MBOX_MAX_MSG_LEN, GFP_KERNEL);
		if (!tdev->rx_buffer)
			return -ENOMEM;
	}

	ret = mbox_test_add_debugfs(pdev, tdev);
	if (ret)
		return ret;

	init_waitqueue_head(&tdev->waitq);
	dev_info(&pdev->dev, "Successfully registered\n");

	return 0;
}