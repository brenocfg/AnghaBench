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
struct wm97xx_platform_data {int /*<<< orphan*/  batt_pdata; int /*<<< orphan*/  ac97; } ;
struct wm97xx {int /*<<< orphan*/  ac97; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int _wm97xx_probe (struct wm97xx*) ; 
 struct wm97xx_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct wm97xx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int wm97xx_add_battery (struct wm97xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm97xx_unregister_touch (struct wm97xx*) ; 

__attribute__((used)) static int wm97xx_mfd_probe(struct platform_device *pdev)
{
	struct wm97xx *wm;
	struct wm97xx_platform_data *mfd_pdata = dev_get_platdata(&pdev->dev);
	int ret;

	wm = devm_kzalloc(&pdev->dev, sizeof(struct wm97xx), GFP_KERNEL);
	if (!wm)
		return -ENOMEM;

	wm->dev = &pdev->dev;
	wm->ac97 = mfd_pdata->ac97;

	ret =  _wm97xx_probe(wm);
	if (ret)
		return ret;

	ret = wm97xx_add_battery(wm, mfd_pdata->batt_pdata);
	if (ret < 0)
		goto batt_err;

	return ret;

batt_err:
	wm97xx_unregister_touch(wm);
	return ret;
}