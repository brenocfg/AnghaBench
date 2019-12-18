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
typedef  int u16 ;
struct wm97xx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_AUX ; 
 int /*<<< orphan*/  AC97_VIDEO ; 
 int /*<<< orphan*/  AC97_WM97XX_DIGITISER1 ; 
 int /*<<< orphan*/  AC97_WM97XX_DIGITISER2 ; 
 int WM9705_PIL ; 
 int WM97XX_DELAY (int) ; 
 int WM97XX_RPR ; 
 int delay ; 
 int* delay_table ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int mask ; 
 int pdd ; 
 int pil ; 
 scalar_t__ pressure ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wm9705_phy_init(struct wm97xx *wm)
{
	u16 dig1 = 0, dig2 = WM97XX_RPR;

	/*
	* mute VIDEO and AUX as they share X and Y touchscreen
	* inputs on the WM9705
	*/
	wm97xx_reg_write(wm, AC97_AUX, 0x8000);
	wm97xx_reg_write(wm, AC97_VIDEO, 0x8000);

	/* touchpanel pressure current*/
	if (pil == 2) {
		dig2 |= WM9705_PIL;
		dev_dbg(wm->dev,
			"setting pressure measurement current to 400uA.");
	} else if (pil)
		dev_dbg(wm->dev,
			"setting pressure measurement current to 200uA.");
	if (!pil)
		pressure = 0;

	/* polling mode sample settling delay */
	if (delay != 4) {
		if (delay < 0 || delay > 15) {
			dev_dbg(wm->dev, "supplied delay out of range.");
			delay = 4;
		}
	}
	dig1 &= 0xff0f;
	dig1 |= WM97XX_DELAY(delay);
	dev_dbg(wm->dev, "setting adc sample delay to %d u Secs.",
		delay_table[delay]);

	/* WM9705 pdd */
	dig2 |= (pdd & 0x000f);
	dev_dbg(wm->dev, "setting pdd to Vmid/%d", 1 - (pdd & 0x000f));

	/* mask */
	dig2 |= ((mask & 0x3) << 4);

	wm97xx_reg_write(wm, AC97_WM97XX_DIGITISER1, dig1);
	wm97xx_reg_write(wm, AC97_WM97XX_DIGITISER2, dig2);
}