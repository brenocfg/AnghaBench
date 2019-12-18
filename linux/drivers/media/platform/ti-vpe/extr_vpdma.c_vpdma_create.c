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
struct vpdma_data {void (* cb ) (struct platform_device*) ;int /*<<< orphan*/  base; int /*<<< orphan*/  lock; struct platform_device* pdev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  VPDMA_FIRMWARE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int vpdma_load_firmware (struct vpdma_data*) ; 

int vpdma_create(struct platform_device *pdev, struct vpdma_data *vpdma,
		void (*cb)(struct platform_device *pdev))
{
	struct resource *res;
	int r;

	dev_dbg(&pdev->dev, "vpdma_create\n");

	vpdma->pdev = pdev;
	vpdma->cb = cb;
	spin_lock_init(&vpdma->lock);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "vpdma");
	if (res == NULL) {
		dev_err(&pdev->dev, "missing platform resources data\n");
		return -ENODEV;
	}

	vpdma->base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (!vpdma->base) {
		dev_err(&pdev->dev, "failed to ioremap\n");
		return -ENOMEM;
	}

	r = vpdma_load_firmware(vpdma);
	if (r) {
		pr_err("failed to load firmware %s\n", VPDMA_FIRMWARE);
		return r;
	}

	return 0;
}