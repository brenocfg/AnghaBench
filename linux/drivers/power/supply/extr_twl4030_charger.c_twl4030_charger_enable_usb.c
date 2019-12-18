#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct twl4030_bci {scalar_t__ usb_mode; int usb_enabled; scalar_t__ usb_cur; TYPE_1__* transceiver; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CHARGE_AUTO ; 
 scalar_t__ CHARGE_LINEAR ; 
 scalar_t__ CHARGE_OFF ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_1__*) ; 
 int TWL4030_BATSTS ; 
 int TWL4030_BCIAUTOAC ; 
 int TWL4030_BCIAUTOUSB ; 
 int /*<<< orphan*/  TWL4030_BCIMDKEY ; 
 int /*<<< orphan*/  TWL4030_BCIMFEN3 ; 
 int /*<<< orphan*/  TWL4030_BCIMFKEY ; 
 int /*<<< orphan*/  TWL4030_BCIMFSTS4 ; 
 int /*<<< orphan*/  TWL4030_BCIWDKEY ; 
 int TWL4030_CVENAC ; 
 int TWL4030_ICHGEOC ; 
 int TWL4030_ICHGLOW ; 
 int /*<<< orphan*/  TWL4030_INTERRUPTS_BCIIMR1A ; 
 int /*<<< orphan*/  TWL4030_MODULE_INTERRUPTS ; 
 int TWL4030_TBATOR1 ; 
 int TWL4030_TBATOR2 ; 
 int /*<<< orphan*/  TWL4030_USBFASTMCHG ; 
 int /*<<< orphan*/  TWL_MODULE_MAIN_CHARGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_charger_update_current (struct twl4030_bci*) ; 
 int twl4030_clear_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int twl4030_clear_set_boot_bci (int,int) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_charger_enable_usb(struct twl4030_bci *bci, bool enable)
{
	int ret;
	u32 reg;

	if (bci->usb_mode == CHARGE_OFF)
		enable = false;
	if (enable && !IS_ERR_OR_NULL(bci->transceiver)) {

		twl4030_charger_update_current(bci);

		/* Need to keep phy powered */
		if (!bci->usb_enabled) {
			pm_runtime_get_sync(bci->transceiver->dev);
			bci->usb_enabled = 1;
		}

		if (bci->usb_mode == CHARGE_AUTO) {
			/* Enable interrupts now. */
			reg = ~(u32)(TWL4030_ICHGLOW | TWL4030_ICHGEOC |
					TWL4030_TBATOR2 | TWL4030_TBATOR1 |
					TWL4030_BATSTS);
			ret = twl_i2c_write_u8(TWL4030_MODULE_INTERRUPTS, reg,
				       TWL4030_INTERRUPTS_BCIIMR1A);
			if (ret < 0) {
				dev_err(bci->dev,
					"failed to unmask interrupts: %d\n",
					ret);
				return ret;
			}
			/* forcing the field BCIAUTOUSB (BOOT_BCI[1]) to 1 */
			ret = twl4030_clear_set_boot_bci(0, TWL4030_BCIAUTOUSB);
		}

		/* forcing USBFASTMCHG(BCIMFSTS4[2]) to 1 */
		ret = twl4030_clear_set(TWL_MODULE_MAIN_CHARGE, 0,
			TWL4030_USBFASTMCHG, TWL4030_BCIMFSTS4);
		if (bci->usb_mode == CHARGE_LINEAR) {
			/* Enable interrupts now. */
			reg = ~(u32)(TWL4030_ICHGLOW | TWL4030_TBATOR2 |
					TWL4030_TBATOR1 | TWL4030_BATSTS);
			ret = twl_i2c_write_u8(TWL4030_MODULE_INTERRUPTS, reg,
				       TWL4030_INTERRUPTS_BCIIMR1A);
			if (ret < 0) {
				dev_err(bci->dev,
					"failed to unmask interrupts: %d\n",
					ret);
				return ret;
			}
			twl4030_clear_set_boot_bci(TWL4030_BCIAUTOAC|TWL4030_CVENAC, 0);
			/* Watch dog key: WOVF acknowledge */
			ret = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE, 0x33,
					       TWL4030_BCIWDKEY);
			/* 0x24 + EKEY6: off mode */
			ret = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE, 0x2a,
					       TWL4030_BCIMDKEY);
			/* EKEY2: Linear charge: USB path */
			ret = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE, 0x26,
					       TWL4030_BCIMDKEY);
			/* WDKEY5: stop watchdog count */
			ret = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE, 0xf3,
					       TWL4030_BCIWDKEY);
			/* enable MFEN3 access */
			ret = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE, 0x9c,
					       TWL4030_BCIMFKEY);
			 /* ICHGEOCEN - end-of-charge monitor (current < 80mA)
			  *                      (charging continues)
			  * ICHGLOWEN - current level monitor (charge continues)
			  * don't monitor over-current or heat save
			  */
			ret = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE, 0xf0,
					       TWL4030_BCIMFEN3);
		}
	} else {
		ret = twl4030_clear_set_boot_bci(TWL4030_BCIAUTOUSB, 0);
		ret |= twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE, 0x2a,
					TWL4030_BCIMDKEY);
		if (bci->usb_enabled) {
			pm_runtime_mark_last_busy(bci->transceiver->dev);
			pm_runtime_put_autosuspend(bci->transceiver->dev);
			bci->usb_enabled = 0;
		}
		bci->usb_cur = 0;
	}

	return ret;
}