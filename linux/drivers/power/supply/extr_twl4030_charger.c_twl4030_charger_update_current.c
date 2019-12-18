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
typedef  int u8 ;
struct twl4030_bci {int ac_cur; int ac_is_active; int usb_cur; int usb_cur_target; int ichg_eoc; int ichg_lo; int ichg_hi; int /*<<< orphan*/  current_worker; int /*<<< orphan*/  channel_vac; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_BCICTL1 ; 
 int /*<<< orphan*/  TWL4030_BCIIREF1 ; 
 int /*<<< orphan*/  TWL4030_BCIIREF2 ; 
 int /*<<< orphan*/  TWL4030_BCIMFKEY ; 
 int /*<<< orphan*/  TWL4030_BCIMFTH8 ; 
 int /*<<< orphan*/  TWL4030_BCIMFTH9 ; 
 int TWL4030_CGAIN ; 
 int /*<<< orphan*/  TWL4030_PM_MASTER_BOOT_BCI ; 
 int /*<<< orphan*/  TWL_MODULE_MAIN_CHARGE ; 
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 int /*<<< orphan*/  USB_CUR_DELAY ; 
 scalar_t__ ac_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int twl4030_bci_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  twl4030_clear_set_boot_bci (int,int) ; 
 scalar_t__ twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned int ua2regval (int,int) ; 

__attribute__((used)) static int twl4030_charger_update_current(struct twl4030_bci *bci)
{
	int status;
	int cur;
	unsigned reg, cur_reg;
	u8 bcictl1, oldreg, fullreg;
	bool cgain = false;
	u8 boot_bci;

	/*
	 * If AC (Accessory Charger) voltage exceeds 4.5V (MADC 11)
	 * and AC is enabled, set current for 'ac'
	 */
	if (ac_available(bci->channel_vac)) {
		cur = bci->ac_cur;
		bci->ac_is_active = true;
	} else {
		cur = bci->usb_cur;
		bci->ac_is_active = false;
		if (cur > bci->usb_cur_target) {
			cur = bci->usb_cur_target;
			bci->usb_cur = cur;
		}
		if (cur < bci->usb_cur_target)
			schedule_delayed_work(&bci->current_worker, USB_CUR_DELAY);
	}

	/* First, check thresholds and see if cgain is needed */
	if (bci->ichg_eoc >= 200000)
		cgain = true;
	if (bci->ichg_lo >= 400000)
		cgain = true;
	if (bci->ichg_hi >= 820000)
		cgain = true;
	if (cur > 852000)
		cgain = true;

	status = twl4030_bci_read(TWL4030_BCICTL1, &bcictl1);
	if (status < 0)
		return status;
	if (twl_i2c_read_u8(TWL_MODULE_PM_MASTER, &boot_bci,
			    TWL4030_PM_MASTER_BOOT_BCI) < 0)
		boot_bci = 0;
	boot_bci &= 7;

	if ((!!cgain) != !!(bcictl1 & TWL4030_CGAIN))
		/* Need to turn for charging while we change the
		 * CGAIN bit.  Leave it off while everything is
		 * updated.
		 */
		twl4030_clear_set_boot_bci(boot_bci, 0);

	/*
	 * For ichg_eoc, the hardware only supports reg values matching
	 * 100XXXX000, and requires the XXXX be stored in the high nibble
	 * of TWL4030_BCIMFTH8.
	 */
	reg = ua2regval(bci->ichg_eoc, cgain);
	if (reg > 0x278)
		reg = 0x278;
	if (reg < 0x200)
		reg = 0x200;
	reg = (reg >> 3) & 0xf;
	fullreg = reg << 4;

	/*
	 * For ichg_lo, reg value must match 10XXXX0000.
	 * XXXX is stored in low nibble of TWL4030_BCIMFTH8.
	 */
	reg = ua2regval(bci->ichg_lo, cgain);
	if (reg > 0x2F0)
		reg = 0x2F0;
	if (reg < 0x200)
		reg = 0x200;
	reg = (reg >> 4) & 0xf;
	fullreg |= reg;

	/* ichg_eoc and ichg_lo live in same register */
	status = twl4030_bci_read(TWL4030_BCIMFTH8, &oldreg);
	if (status < 0)
		return status;
	if (oldreg != fullreg) {
		status = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE, 0xF4,
					  TWL4030_BCIMFKEY);
		if (status < 0)
			return status;
		twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE,
				 fullreg, TWL4030_BCIMFTH8);
	}

	/* ichg_hi threshold must be 1XXXX01100 (I think) */
	reg = ua2regval(bci->ichg_hi, cgain);
	if (reg > 0x3E0)
		reg = 0x3E0;
	if (reg < 0x200)
		reg = 0x200;
	fullreg = (reg >> 5) & 0xF;
	fullreg <<= 4;
	status = twl4030_bci_read(TWL4030_BCIMFTH9, &oldreg);
	if (status < 0)
		return status;
	if ((oldreg & 0xF0) != fullreg) {
		fullreg |= (oldreg & 0x0F);
		status = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE, 0xE7,
					  TWL4030_BCIMFKEY);
		if (status < 0)
			return status;
		twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE,
				 fullreg, TWL4030_BCIMFTH9);
	}

	/*
	 * And finally, set the current.  This is stored in
	 * two registers.
	 */
	reg = ua2regval(cur, cgain);
	/* we have only 10 bits */
	if (reg > 0x3ff)
		reg = 0x3ff;
	status = twl4030_bci_read(TWL4030_BCIIREF1, &oldreg);
	if (status < 0)
		return status;
	cur_reg = oldreg;
	status = twl4030_bci_read(TWL4030_BCIIREF2, &oldreg);
	if (status < 0)
		return status;
	cur_reg |= oldreg << 8;
	if (reg != oldreg) {
		/* disable write protection for one write access for
		 * BCIIREF */
		status = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE, 0xE7,
					  TWL4030_BCIMFKEY);
		if (status < 0)
			return status;
		status = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE,
					  (reg & 0x100) ? 3 : 2,
					  TWL4030_BCIIREF2);
		if (status < 0)
			return status;
		/* disable write protection for one write access for
		 * BCIIREF */
		status = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE, 0xE7,
					  TWL4030_BCIMFKEY);
		if (status < 0)
			return status;
		status = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE,
					  reg & 0xff,
					  TWL4030_BCIIREF1);
	}
	if ((!!cgain) != !!(bcictl1 & TWL4030_CGAIN)) {
		/* Flip CGAIN and re-enable charging */
		bcictl1 ^= TWL4030_CGAIN;
		twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE,
				 bcictl1, TWL4030_BCICTL1);
		twl4030_clear_set_boot_bci(0, boot_bci);
	}
	return 0;
}