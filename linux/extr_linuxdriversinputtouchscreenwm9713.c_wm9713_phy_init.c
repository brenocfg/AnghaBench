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
struct wm97xx {int /*<<< orphan*/  misc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_GPIO_STICKY ; 
 int /*<<< orphan*/  AC97_WM9713_DIG1 ; 
 int /*<<< orphan*/  AC97_WM9713_DIG2 ; 
 int /*<<< orphan*/  AC97_WM9713_DIG3 ; 
 int WM9712_PIL ; 
 int WM9712_RPU (int) ; 
 int WM9713_45W ; 
 int WM9713_WAIT ; 
 int WM97XX_DELAY (int) ; 
 int WM97XX_SLT (int) ; 
 scalar_t__ coord ; 
 int delay ; 
 int* delay_table ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ five_wire ; 
 int mask ; 
 int pil ; 
 scalar_t__ pressure ; 
 int rpu ; 
 int /*<<< orphan*/  wm97xx_reg_read (struct wm97xx*,int) ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wm9713_phy_init(struct wm97xx *wm)
{
	u16 dig1 = 0, dig2, dig3;

	/* default values */
	dig2 = WM97XX_DELAY(4) | WM97XX_SLT(5);
	dig3 = WM9712_RPU(1);

	/* rpu */
	if (rpu) {
		dig3 &= 0xffc0;
		dig3 |= WM9712_RPU(rpu);
		dev_info(wm->dev, "setting pen detect pull-up to %d Ohms\n",
			 64000 / rpu);
	}

	/* Five wire panel? */
	if (five_wire) {
		dig3 |= WM9713_45W;
		dev_info(wm->dev, "setting 5-wire touchscreen mode.");

		if (pil) {
			dev_warn(wm->dev,
				 "Pressure measurement not supported in 5 "
				 "wire mode, disabling\n");
			pil = 0;
		}
	}

	/* touchpanel pressure */
	if (pil == 2) {
		dig3 |= WM9712_PIL;
		dev_info(wm->dev,
			 "setting pressure measurement current to 400uA.");
	} else if (pil)
		dev_info(wm->dev,
			 "setting pressure measurement current to 200uA.");
	if (!pil)
		pressure = 0;

	/* sample settling delay */
	if (delay < 0 || delay > 15) {
		dev_info(wm->dev, "supplied delay out of range.");
		delay = 4;
		dev_info(wm->dev, "setting adc sample delay to %d u Secs.",
			 delay_table[delay]);
	}
	dig2 &= 0xff0f;
	dig2 |= WM97XX_DELAY(delay);

	/* mask */
	dig3 |= ((mask & 0x3) << 4);
	if (coord)
		dig3 |= WM9713_WAIT;

	wm->misc = wm97xx_reg_read(wm, 0x5a);

	wm97xx_reg_write(wm, AC97_WM9713_DIG1, dig1);
	wm97xx_reg_write(wm, AC97_WM9713_DIG2, dig2);
	wm97xx_reg_write(wm, AC97_WM9713_DIG3, dig3);
	wm97xx_reg_write(wm, AC97_GPIO_STICKY, 0x0);
}