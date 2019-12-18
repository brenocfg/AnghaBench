#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pcf50633_mbc {int /*<<< orphan*/  usb; TYPE_2__* pcf; } ;
struct pcf50633 {int /*<<< orphan*/  dev; int /*<<< orphan*/  mbc_pdev; } ;
struct TYPE_5__ {TYPE_1__* pdata; } ;
struct TYPE_4__ {int charger_reference_current_ma; } ;

/* Variables and functions */
 int PCF50633_MBCC1_CHGENA ; 
 int PCF50633_MBCC7_USB_1000mA ; 
 int PCF50633_MBCC7_USB_100mA ; 
 int PCF50633_MBCC7_USB_500mA ; 
 int PCF50633_MBCC7_USB_MASK ; 
 int PCF50633_MBCC7_USB_SUSPEND ; 
 int PCF50633_MBCS2_MBC_BAT_FULL ; 
 int PCF50633_MBCS2_MBC_MASK ; 
 int /*<<< orphan*/  PCF50633_REG_MBCC1 ; 
 int /*<<< orphan*/  PCF50633_REG_MBCC5 ; 
 int /*<<< orphan*/  PCF50633_REG_MBCC7 ; 
 int /*<<< orphan*/  PCF50633_REG_MBCS2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pcf50633_reg_clear_bits (struct pcf50633*,int /*<<< orphan*/ ,int) ; 
 int pcf50633_reg_read (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int pcf50633_reg_set_bit_mask (struct pcf50633*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pcf50633_reg_write (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 struct pcf50633_mbc* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

int pcf50633_mbc_usb_curlim_set(struct pcf50633 *pcf, int ma)
{
	struct pcf50633_mbc *mbc = platform_get_drvdata(pcf->mbc_pdev);
	int ret = 0;
	u8 bits;
	u8 mbcs2, chgmod;
	unsigned int mbcc5;

	if (ma >= 1000) {
		bits = PCF50633_MBCC7_USB_1000mA;
		ma = 1000;
	} else if (ma >= 500) {
		bits = PCF50633_MBCC7_USB_500mA;
		ma = 500;
	} else if (ma >= 100) {
		bits = PCF50633_MBCC7_USB_100mA;
		ma = 100;
	} else {
		bits = PCF50633_MBCC7_USB_SUSPEND;
		ma = 0;
	}

	ret = pcf50633_reg_set_bit_mask(pcf, PCF50633_REG_MBCC7,
					PCF50633_MBCC7_USB_MASK, bits);
	if (ret)
		dev_err(pcf->dev, "error setting usb curlim to %d mA\n", ma);
	else
		dev_info(pcf->dev, "usb curlim to %d mA\n", ma);

	/*
	 * We limit the charging current to be the USB current limit.
	 * The reason is that on pcf50633, when it enters PMU Standby mode,
	 * which it does when the device goes "off", the USB current limit
	 * reverts to the variant default.  In at least one common case, that
	 * default is 500mA.  By setting the charging current to be the same
	 * as the USB limit we set here before PMU standby, we enforce it only
	 * using the correct amount of current even when the USB current limit
	 * gets reset to the wrong thing
	 */

	if (mbc->pcf->pdata->charger_reference_current_ma) {
		mbcc5 = (ma << 8) / mbc->pcf->pdata->charger_reference_current_ma;
		if (mbcc5 > 255)
			mbcc5 = 255;
		pcf50633_reg_write(mbc->pcf, PCF50633_REG_MBCC5, mbcc5);
	}

	mbcs2 = pcf50633_reg_read(mbc->pcf, PCF50633_REG_MBCS2);
	chgmod = (mbcs2 & PCF50633_MBCS2_MBC_MASK);

	/* If chgmod == BATFULL, setting chgena has no effect.
	 * Datasheet says we need to set resume instead but when autoresume is
	 * used resume doesn't work. Clear and set chgena instead.
	 */
	if (chgmod != PCF50633_MBCS2_MBC_BAT_FULL)
		pcf50633_reg_set_bit_mask(pcf, PCF50633_REG_MBCC1,
				PCF50633_MBCC1_CHGENA, PCF50633_MBCC1_CHGENA);
	else {
		pcf50633_reg_clear_bits(pcf, PCF50633_REG_MBCC1,
				PCF50633_MBCC1_CHGENA);
		pcf50633_reg_set_bit_mask(pcf, PCF50633_REG_MBCC1,
				PCF50633_MBCC1_CHGENA, PCF50633_MBCC1_CHGENA);
	}

	power_supply_changed(mbc->usb);

	return ret;
}