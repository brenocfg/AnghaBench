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
struct rtsx_chip {int ocp_stat; int card_exist; int card_fail; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_OE ; 
 int MS_CARD ; 
 int /*<<< orphan*/  MS_OUTPUT_EN ; 
 int SD_CARD ; 
 int SD_OC_EVER ; 
 int SD_OC_NOW ; 
 int /*<<< orphan*/  SD_OUTPUT_EN ; 
 int XD_CARD ; 
 int /*<<< orphan*/  XD_OUTPUT_EN ; 
 int /*<<< orphan*/  card_power_off (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtsx_manage_1lun_mode(struct rtsx_chip *chip)
{
#ifdef SUPPORT_OCP
	if (!(chip->ocp_stat & (SD_OC_NOW | SD_OC_EVER)))
		return;

	dev_dbg(rtsx_dev(chip), "Over current, OCPSTAT is 0x%x\n",
		chip->ocp_stat);

	if (chip->card_exist & SD_CARD) {
		rtsx_write_register(chip, CARD_OE, SD_OUTPUT_EN, 0);
		chip->card_fail |= SD_CARD;
	} else if (chip->card_exist & MS_CARD) {
		rtsx_write_register(chip, CARD_OE, MS_OUTPUT_EN, 0);
		chip->card_fail |= MS_CARD;
	} else if (chip->card_exist & XD_CARD) {
		rtsx_write_register(chip, CARD_OE, XD_OUTPUT_EN, 0);
		chip->card_fail |= XD_CARD;
	}
	card_power_off(chip, SD_CARD);
#endif
}