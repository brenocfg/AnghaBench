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
struct wm97xx_pdata {int /*<<< orphan*/ * batt_pdata; } ;
struct wm97xx {int /*<<< orphan*/  ac97; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int _wm97xx_probe (struct wm97xx*) ; 
 struct wm97xx_pdata* dev_get_platdata (struct device*) ; 
 struct wm97xx* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_ac97_t (struct device*) ; 
 int wm97xx_add_battery (struct wm97xx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm97xx_unregister_touch (struct wm97xx*) ; 

__attribute__((used)) static int wm97xx_probe(struct device *dev)
{
	struct wm97xx *wm;
	int ret;
	struct wm97xx_pdata *pdata = dev_get_platdata(dev);

	wm = devm_kzalloc(dev, sizeof(struct wm97xx), GFP_KERNEL);
	if (!wm)
		return -ENOMEM;

	wm->dev = dev;
	wm->ac97 = to_ac97_t(dev);

	ret =  _wm97xx_probe(wm);
	if (ret)
		return ret;

	ret = wm97xx_add_battery(wm, pdata ? pdata->batt_pdata : NULL);
	if (ret < 0)
		goto batt_err;

	return ret;

batt_err:
	wm97xx_unregister_touch(wm);
	return ret;
}