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
struct cc_data {TYPE_1__* res; int /*<<< orphan*/  base; } ;
struct cal_dev {struct platform_device* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct cc_data* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct cc_data* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cal_dbg (int,struct cal_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cal_err (struct cal_dev*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct cc_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct cc_data *cc_create(struct cal_dev *dev, unsigned int core)
{
	struct platform_device *pdev = dev->pdev;
	struct cc_data *cc;

	cc = devm_kzalloc(&pdev->dev, sizeof(*cc), GFP_KERNEL);
	if (!cc)
		return ERR_PTR(-ENOMEM);

	cc->res = platform_get_resource_byname(pdev,
					       IORESOURCE_MEM,
					       (core == 0) ?
						"cal_rx_core0" :
						"cal_rx_core1");
	cc->base = devm_ioremap_resource(&pdev->dev, cc->res);
	if (IS_ERR(cc->base)) {
		cal_err(dev, "failed to ioremap\n");
		return ERR_CAST(cc->base);
	}

	cal_dbg(1, dev, "ioresource %s at %pa - %pa\n",
		cc->res->name, &cc->res->start, &cc->res->end);

	return cc;
}