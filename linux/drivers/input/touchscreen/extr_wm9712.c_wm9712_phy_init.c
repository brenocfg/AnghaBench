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
 int /*<<< orphan*/  AC97_GPIO_CFG ; 
 int /*<<< orphan*/  AC97_MISC_AFE ; 
 int /*<<< orphan*/  AC97_WM97XX_DIGITISER1 ; 
 int /*<<< orphan*/  AC97_WM97XX_DIGITISER2 ; 
 int WM9712_45W ; 
 int WM9712_PIL ; 
 int WM9712_RPU (int) ; 
 int WM9712_WAIT ; 
 int WM97XX_DELAY (int) ; 
 int WM97XX_GPIO_4 ; 
 int WM97XX_RPR ; 
 scalar_t__ coord ; 
 int delay ; 
 int* delay_table ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ five_wire ; 
 int mask ; 
 int pil ; 
 scalar_t__ pressure ; 
 int rpu ; 
 int wm97xx_reg_read (struct wm97xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wm9712_phy_init(struct wm97xx *wm)
{
	u16 dig1 = 0;
	u16 dig2 = WM97XX_RPR | WM9712_RPU(1);

	/* WM9712 rpu */
	if (rpu) {
		dig2 &= 0xffc0;
		dig2 |= WM9712_RPU(rpu);
		dev_dbg(wm->dev, "setting pen detect pull-up to %d Ohms\n",
			64000 / rpu);
	}

	/* WM9712 five wire */
	if (five_wire) {
		dig2 |= WM9712_45W;
		dev_dbg(wm->dev, "setting 5-wire touchscreen mode.\n");

		if (pil) {
			dev_warn(wm->dev, "pressure measurement is not "
				 "supported in 5-wire mode\n");
			pil = 0;
		}
	}

	/* touchpanel pressure current*/
	if (pil == 2) {
		dig2 |= WM9712_PIL;
		dev_dbg(wm->dev,
			"setting pressure measurement current to 400uA.\n");
	} else if (pil)
		dev_dbg(wm->dev,
			"setting pressure measurement current to 200uA.\n");
	if (!pil)
		pressure = 0;

	/* polling mode sample settling delay */
	if (delay < 0 || delay > 15) {
		dev_dbg(wm->dev, "supplied delay out of range.\n");
		delay = 4;
	}
	dig1 &= 0xff0f;
	dig1 |= WM97XX_DELAY(delay);
	dev_dbg(wm->dev, "setting adc sample delay to %d u Secs.\n",
		delay_table[delay]);

	/* mask */
	dig2 |= ((mask & 0x3) << 6);
	if (mask) {
		u16 reg;
		/* Set GPIO4 as Mask Pin*/
		reg = wm97xx_reg_read(wm, AC97_MISC_AFE);
		wm97xx_reg_write(wm, AC97_MISC_AFE, reg | WM97XX_GPIO_4);
		reg = wm97xx_reg_read(wm, AC97_GPIO_CFG);
		wm97xx_reg_write(wm, AC97_GPIO_CFG, reg | WM97XX_GPIO_4);
	}

	/* wait - coord mode */
	if (coord)
		dig2 |= WM9712_WAIT;

	wm97xx_reg_write(wm, AC97_WM97XX_DIGITISER1, dig1);
	wm97xx_reg_write(wm, AC97_WM97XX_DIGITISER2, dig2);
}