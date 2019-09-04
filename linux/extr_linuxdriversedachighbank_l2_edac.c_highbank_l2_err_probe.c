#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_13__ {TYPE_1__* driver; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {char* compatible; } ;
struct hb_l2_drvdata {void* sb_irq; void* db_irq; int /*<<< orphan*/  base; } ;
struct edac_device_ctl_info {char* ctl_name; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  mod_name; TYPE_2__* dev; struct hb_l2_drvdata* pvt_info; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  devm_request_mem_region (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_close_group (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devres_open_group (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_release_group (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ edac_device_add_device (struct edac_device_ctl_info*) ; 
 struct edac_device_ctl_info* edac_device_alloc_ctl_info (int,char*,int,char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_del_device (TYPE_2__*) ; 
 int /*<<< orphan*/  edac_device_free_ctl_info (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  hb_l2_err_of_match ; 
 int /*<<< orphan*/  highbank_l2_err_handler ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int highbank_l2_err_probe(struct platform_device *pdev)
{
	const struct of_device_id *id;
	struct edac_device_ctl_info *dci;
	struct hb_l2_drvdata *drvdata;
	struct resource *r;
	int res = 0;

	dci = edac_device_alloc_ctl_info(sizeof(*drvdata), "cpu",
		1, "L", 1, 2, NULL, 0, 0);
	if (!dci)
		return -ENOMEM;

	drvdata = dci->pvt_info;
	dci->dev = &pdev->dev;
	platform_set_drvdata(pdev, dci);

	if (!devres_open_group(&pdev->dev, NULL, GFP_KERNEL))
		return -ENOMEM;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r) {
		dev_err(&pdev->dev, "Unable to get mem resource\n");
		res = -ENODEV;
		goto err;
	}

	if (!devm_request_mem_region(&pdev->dev, r->start,
				     resource_size(r), dev_name(&pdev->dev))) {
		dev_err(&pdev->dev, "Error while requesting mem region\n");
		res = -EBUSY;
		goto err;
	}

	drvdata->base = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	if (!drvdata->base) {
		dev_err(&pdev->dev, "Unable to map regs\n");
		res = -ENOMEM;
		goto err;
	}

	id = of_match_device(hb_l2_err_of_match, &pdev->dev);
	dci->mod_name = pdev->dev.driver->name;
	dci->ctl_name = id ? id->compatible : "unknown";
	dci->dev_name = dev_name(&pdev->dev);

	if (edac_device_add_device(dci))
		goto err;

	drvdata->db_irq = platform_get_irq(pdev, 0);
	res = devm_request_irq(&pdev->dev, drvdata->db_irq,
			       highbank_l2_err_handler,
			       0, dev_name(&pdev->dev), dci);
	if (res < 0)
		goto err2;

	drvdata->sb_irq = platform_get_irq(pdev, 1);
	res = devm_request_irq(&pdev->dev, drvdata->sb_irq,
			       highbank_l2_err_handler,
			       0, dev_name(&pdev->dev), dci);
	if (res < 0)
		goto err2;

	devres_close_group(&pdev->dev, NULL);
	return 0;
err2:
	edac_device_del_device(&pdev->dev);
err:
	devres_release_group(&pdev->dev, NULL);
	edac_device_free_ctl_info(dci);
	return res;
}