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
struct ms_info {int* raw_sys_info; scalar_t__ switch_8bit_fail; } ;
struct rtsx_chip {int ms_power_class_en; int* card_bus_width; size_t* card2lun; struct ms_info ms_card; } ;

/* Variables and functions */
 scalar_t__ CHK_HG8BIT (struct ms_info*) ; 
 scalar_t__ CHK_MSXC (struct ms_info*) ; 
 size_t MS_CARD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int mg_set_tpc_para_sub (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ms_pro_reset_flow (struct rtsx_chip*,int) ; 
 int ms_read_attribute_info (struct rtsx_chip*) ; 
 int msxc_change_power (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 

__attribute__((used)) static int reset_ms_pro(struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &chip->ms_card;
	int retval;
#ifdef XC_POWERCLASS
	u8 change_power_class;

	if (chip->ms_power_class_en & 0x02)
		change_power_class = 2;
	else if (chip->ms_power_class_en & 0x01)
		change_power_class = 1;
	else
		change_power_class = 0;
#endif

#ifdef XC_POWERCLASS
retry:
#endif
	retval = ms_pro_reset_flow(chip, 1);
	if (retval != STATUS_SUCCESS) {
		if (ms_card->switch_8bit_fail) {
			retval = ms_pro_reset_flow(chip, 0);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;
		} else {
			return STATUS_FAIL;
		}
	}

	retval = ms_read_attribute_info(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

#ifdef XC_POWERCLASS
	if (CHK_HG8BIT(ms_card))
		change_power_class = 0;

	if (change_power_class && CHK_MSXC(ms_card)) {
		u8 power_class_en = chip->ms_power_class_en;

		dev_dbg(rtsx_dev(chip), "power_class_en = 0x%x\n",
			power_class_en);
		dev_dbg(rtsx_dev(chip), "change_power_class = %d\n",
			change_power_class);

		if (change_power_class)
			power_class_en &= (1 << (change_power_class - 1));
		else
			power_class_en = 0;

		if (power_class_en) {
			u8 power_class_mode =
				(ms_card->raw_sys_info[46] & 0x18) >> 3;
			dev_dbg(rtsx_dev(chip), "power_class_mode = 0x%x",
				power_class_mode);
			if (change_power_class > power_class_mode)
				change_power_class = power_class_mode;
			if (change_power_class) {
				retval = msxc_change_power(chip,
							   change_power_class);
				if (retval != STATUS_SUCCESS) {
					change_power_class--;
					goto retry;
				}
			}
		}
	}
#endif

#ifdef SUPPORT_MAGIC_GATE
	retval = mg_set_tpc_para_sub(chip, 0, 0);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;
#endif

	if (CHK_HG8BIT(ms_card))
		chip->card_bus_width[chip->card2lun[MS_CARD]] = 8;
	else
		chip->card_bus_width[chip->card2lun[MS_CARD]] = 4;

	return STATUS_SUCCESS;
}