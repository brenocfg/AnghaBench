#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cm_data {TYPE_1__* res; int /*<<< orphan*/  base; } ;
struct cal_dev {struct platform_device* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct cm_data* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct cm_data* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cal_dbg (int,struct cal_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cal_err (struct cal_dev*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct cm_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct cm_data *cm_create(struct cal_dev *dev)
{
	struct platform_device *pdev = dev->pdev;
	struct cm_data *cm;

	cm = devm_kzalloc(&pdev->dev, sizeof(*cm), GFP_KERNEL);
	if (!cm)
		return ERR_PTR(-ENOMEM);

	cm->res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
						"camerrx_control");
	cm->base = devm_ioremap_resource(&pdev->dev, cm->res);
	if (IS_ERR(cm->base)) {
		cal_err(dev, "failed to ioremap\n");
		return ERR_CAST(cm->base);
	}

	cal_dbg(1, dev, "ioresource %s at %pa - %pa\n",
		cm->res->name, &cm->res->start, &cm->res->end);

	return cm;
}