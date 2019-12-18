#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wm97xx {int id; void** gpio; TYPE_1__* codec; int /*<<< orphan*/  dev; int /*<<< orphan*/  variant; int /*<<< orphan*/  codec_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* phy_init ) (struct wm97xx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_GPIO_CFG ; 
 int /*<<< orphan*/  AC97_GPIO_POLARITY ; 
 int /*<<< orphan*/  AC97_GPIO_STATUS ; 
 int /*<<< orphan*/  AC97_GPIO_STICKY ; 
 int /*<<< orphan*/  AC97_GPIO_WAKEUP ; 
 int /*<<< orphan*/  AC97_MISC_AFE ; 
 int /*<<< orphan*/  AC97_VENDOR_ID1 ; 
 int /*<<< orphan*/  AC97_VENDOR_ID2 ; 
 int ENODEV ; 
 int WM97XX_ID1 ; 
 int /*<<< orphan*/  WM97xx_GENERIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct wm97xx*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct wm97xx*) ; 
 TYPE_1__ wm9705_codec ; 
 TYPE_1__ wm9712_codec ; 
 TYPE_1__ wm9713_codec ; 
 void* wm97xx_reg_read (struct wm97xx*,int /*<<< orphan*/ ) ; 
 int wm97xx_register_touch (struct wm97xx*) ; 

__attribute__((used)) static int _wm97xx_probe(struct wm97xx *wm)
{
	int id = 0;

	mutex_init(&wm->codec_mutex);
	dev_set_drvdata(wm->dev, wm);

	/* check that we have a supported codec */
	id = wm97xx_reg_read(wm, AC97_VENDOR_ID1);
	if (id != WM97XX_ID1) {
		dev_err(wm->dev,
			"Device with vendor %04x is not a wm97xx\n", id);
		return -ENODEV;
	}

	wm->id = wm97xx_reg_read(wm, AC97_VENDOR_ID2);

	wm->variant = WM97xx_GENERIC;

	dev_info(wm->dev, "detected a wm97%02x codec\n", wm->id & 0xff);

	switch (wm->id & 0xff) {
#ifdef CONFIG_TOUCHSCREEN_WM9705
	case 0x05:
		wm->codec = &wm9705_codec;
		break;
#endif
#ifdef CONFIG_TOUCHSCREEN_WM9712
	case 0x12:
		wm->codec = &wm9712_codec;
		break;
#endif
#ifdef CONFIG_TOUCHSCREEN_WM9713
	case 0x13:
		wm->codec = &wm9713_codec;
		break;
#endif
	default:
		dev_err(wm->dev, "Support for wm97%02x not compiled in.\n",
			wm->id & 0xff);
		return -ENODEV;
	}

	/* set up physical characteristics */
	wm->codec->phy_init(wm);

	/* load gpio cache */
	wm->gpio[0] = wm97xx_reg_read(wm, AC97_GPIO_CFG);
	wm->gpio[1] = wm97xx_reg_read(wm, AC97_GPIO_POLARITY);
	wm->gpio[2] = wm97xx_reg_read(wm, AC97_GPIO_STICKY);
	wm->gpio[3] = wm97xx_reg_read(wm, AC97_GPIO_WAKEUP);
	wm->gpio[4] = wm97xx_reg_read(wm, AC97_GPIO_STATUS);
	wm->gpio[5] = wm97xx_reg_read(wm, AC97_MISC_AFE);

	return wm97xx_register_touch(wm);
}