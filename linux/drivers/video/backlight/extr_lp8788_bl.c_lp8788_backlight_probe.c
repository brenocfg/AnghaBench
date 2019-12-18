#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct lp8788_bl {int /*<<< orphan*/  bl_dev; int /*<<< orphan*/  pdata; struct lp8788* lp; } ;
struct lp8788 {int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  bl_pdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  backlight_update_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct lp8788* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct lp8788_bl* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp8788_attr_group ; 
 int lp8788_backlight_configure (struct lp8788_bl*) ; 
 int lp8788_backlight_register (struct lp8788_bl*) ; 
 int /*<<< orphan*/  lp8788_backlight_unregister (struct lp8788_bl*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lp8788_bl*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp8788_backlight_probe(struct platform_device *pdev)
{
	struct lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	struct lp8788_bl *bl;
	int ret;

	bl = devm_kzalloc(lp->dev, sizeof(struct lp8788_bl), GFP_KERNEL);
	if (!bl)
		return -ENOMEM;

	bl->lp = lp;
	if (lp->pdata)
		bl->pdata = lp->pdata->bl_pdata;

	platform_set_drvdata(pdev, bl);

	ret = lp8788_backlight_configure(bl);
	if (ret) {
		dev_err(lp->dev, "backlight config err: %d\n", ret);
		goto err_dev;
	}

	ret = lp8788_backlight_register(bl);
	if (ret) {
		dev_err(lp->dev, "register backlight err: %d\n", ret);
		goto err_dev;
	}

	ret = sysfs_create_group(&pdev->dev.kobj, &lp8788_attr_group);
	if (ret) {
		dev_err(lp->dev, "register sysfs err: %d\n", ret);
		goto err_sysfs;
	}

	backlight_update_status(bl->bl_dev);

	return 0;

err_sysfs:
	lp8788_backlight_unregister(bl);
err_dev:
	return ret;
}