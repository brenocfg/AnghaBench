#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_2__ {int knows_txdone; int /*<<< orphan*/ * dev; } ;
struct qmp {int /*<<< orphan*/  mbox_chan; TYPE_1__ mbox_client; int /*<<< orphan*/  msgram; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  event; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct qmp* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct qmp*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_request_channel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qmp*) ; 
 int /*<<< orphan*/  qmp_close (struct qmp*) ; 
 int qmp_cooling_devices_register (struct qmp*) ; 
 int /*<<< orphan*/  qmp_intr ; 
 int qmp_open (struct qmp*) ; 
 int qmp_pd_add (struct qmp*) ; 
 int qmp_qdss_clk_add (struct qmp*) ; 
 int /*<<< orphan*/  qmp_qdss_clk_remove (struct qmp*) ; 

__attribute__((used)) static int qmp_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct qmp *qmp;
	int irq;
	int ret;

	qmp = devm_kzalloc(&pdev->dev, sizeof(*qmp), GFP_KERNEL);
	if (!qmp)
		return -ENOMEM;

	qmp->dev = &pdev->dev;
	init_waitqueue_head(&qmp->event);
	mutex_init(&qmp->tx_lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	qmp->msgram = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(qmp->msgram))
		return PTR_ERR(qmp->msgram);

	qmp->mbox_client.dev = &pdev->dev;
	qmp->mbox_client.knows_txdone = true;
	qmp->mbox_chan = mbox_request_channel(&qmp->mbox_client, 0);
	if (IS_ERR(qmp->mbox_chan)) {
		dev_err(&pdev->dev, "failed to acquire ipc mailbox\n");
		return PTR_ERR(qmp->mbox_chan);
	}

	irq = platform_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, irq, qmp_intr, IRQF_ONESHOT,
			       "aoss-qmp", qmp);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to request interrupt\n");
		goto err_free_mbox;
	}

	ret = qmp_open(qmp);
	if (ret < 0)
		goto err_free_mbox;

	ret = qmp_qdss_clk_add(qmp);
	if (ret)
		goto err_close_qmp;

	ret = qmp_pd_add(qmp);
	if (ret)
		goto err_remove_qdss_clk;

	ret = qmp_cooling_devices_register(qmp);
	if (ret)
		dev_err(&pdev->dev, "failed to register aoss cooling devices\n");

	platform_set_drvdata(pdev, qmp);

	return 0;

err_remove_qdss_clk:
	qmp_qdss_clk_remove(qmp);
err_close_qmp:
	qmp_close(qmp);
err_free_mbox:
	mbox_free_channel(qmp->mbox_chan);

	return ret;
}