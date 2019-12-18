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
struct rtsx_chip {int need_release; int int_reg; int card_exist; int ocp_stat; int card_ejected; int card_fail; size_t* card2lun; scalar_t__ need_reinit; scalar_t__ need_reset; scalar_t__* rw_fail_cnt; int /*<<< orphan*/  lun_mc; int /*<<< orphan*/  sd_io; } ;

/* Variables and functions */
 int CARD_OC_CLR ; 
 int CARD_OC_EVER ; 
 int CARD_OC_INT_CLR ; 
 int CARD_OC_NOW ; 
 scalar_t__ CHECK_BARO_PKG (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 scalar_t__ CHECK_PID (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  CLR_BIT (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HOST_SLEEP_STATE ; 
 int /*<<< orphan*/  LED_GPIO ; 
 int MS_CARD ; 
 int /*<<< orphan*/  MS_NR ; 
 int /*<<< orphan*/  OCPCLR ; 
 int OC_PDCTL ; 
 int /*<<< orphan*/  QFN ; 
 int /*<<< orphan*/  RBCTL ; 
 int RB_FLUSH ; 
 int /*<<< orphan*/  RTSX_CLR_DELINK (struct rtsx_chip*) ; 
 int /*<<< orphan*/  RTSX_STAT_RUN ; 
 scalar_t__ RTSX_STAT_SS ; 
 scalar_t__ RTSX_TST_DELINK (struct rtsx_chip*) ; 
 int SD_CARD ; 
 int /*<<< orphan*/  SD_NR ; 
 int SSC_PDCTL ; 
 int XD_CARD ; 
 int XD_EXIST ; 
 int /*<<< orphan*/  XD_NR ; 
 int /*<<< orphan*/  card_cd_debounce (struct rtsx_chip*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  release_ms_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  release_sd_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  release_sdio (struct rtsx_chip*) ; 
 int /*<<< orphan*/  release_xd_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_force_power_on (struct rtsx_chip*,int) ; 
 scalar_t__ rtsx_get_stat (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_reinit_cards (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_reset_cards (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_reset_chip (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  turn_off_led (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

void rtsx_init_cards(struct rtsx_chip *chip)
{
	if (RTSX_TST_DELINK(chip) && (rtsx_get_stat(chip) != RTSX_STAT_SS)) {
		dev_dbg(rtsx_dev(chip), "Reset chip in polling thread!\n");
		rtsx_reset_chip(chip);
		RTSX_CLR_DELINK(chip);
	}

#ifdef DISABLE_CARD_INT
	card_cd_debounce(chip, &chip->need_reset, &chip->need_release);
#endif

	if (chip->need_release) {
		if (CHECK_PID(chip, 0x5288) && CHECK_BARO_PKG(chip, QFN)) {
			if (chip->int_reg & XD_EXIST) {
				clear_bit(SD_NR, &chip->need_release);
				clear_bit(MS_NR, &chip->need_release);
			}
		}

		if (!(chip->card_exist & SD_CARD) && !chip->sd_io)
			clear_bit(SD_NR, &chip->need_release);
		if (!(chip->card_exist & XD_CARD))
			clear_bit(XD_NR, &chip->need_release);
		if (!(chip->card_exist & MS_CARD))
			clear_bit(MS_NR, &chip->need_release);

		dev_dbg(rtsx_dev(chip), "chip->need_release = 0x%x\n",
			(unsigned int)(chip->need_release));

#ifdef SUPPORT_OCP
		if (chip->need_release) {
			if (chip->ocp_stat & (CARD_OC_NOW | CARD_OC_EVER))
				rtsx_write_register(chip, OCPCLR,
						    CARD_OC_INT_CLR |
						    CARD_OC_CLR,
						    CARD_OC_INT_CLR |
						    CARD_OC_CLR);
			chip->ocp_stat = 0;
		}
#endif
		if (chip->need_release) {
			rtsx_set_stat(chip, RTSX_STAT_RUN);
			rtsx_force_power_on(chip, SSC_PDCTL | OC_PDCTL);
		}

		if (chip->need_release & SD_CARD) {
			clear_bit(SD_NR, &chip->need_release);
			chip->card_exist &= ~SD_CARD;
			chip->card_ejected &= ~SD_CARD;
			chip->card_fail &= ~SD_CARD;
			CLR_BIT(chip->lun_mc, chip->card2lun[SD_CARD]);
			chip->rw_fail_cnt[chip->card2lun[SD_CARD]] = 0;
			rtsx_write_register(chip, RBCTL, RB_FLUSH, RB_FLUSH);

			release_sdio(chip);
			release_sd_card(chip);
		}

		if (chip->need_release & XD_CARD) {
			clear_bit(XD_NR, &chip->need_release);
			chip->card_exist &= ~XD_CARD;
			chip->card_ejected &= ~XD_CARD;
			chip->card_fail &= ~XD_CARD;
			CLR_BIT(chip->lun_mc, chip->card2lun[XD_CARD]);
			chip->rw_fail_cnt[chip->card2lun[XD_CARD]] = 0;

			release_xd_card(chip);

			if (CHECK_PID(chip, 0x5288) &&
			    CHECK_BARO_PKG(chip, QFN))
				rtsx_write_register(chip, HOST_SLEEP_STATE,
						    0xC0, 0xC0);
		}

		if (chip->need_release & MS_CARD) {
			clear_bit(MS_NR, &chip->need_release);
			chip->card_exist &= ~MS_CARD;
			chip->card_ejected &= ~MS_CARD;
			chip->card_fail &= ~MS_CARD;
			CLR_BIT(chip->lun_mc, chip->card2lun[MS_CARD]);
			chip->rw_fail_cnt[chip->card2lun[MS_CARD]] = 0;

			release_ms_card(chip);
		}

		dev_dbg(rtsx_dev(chip), "chip->card_exist = 0x%x\n",
			chip->card_exist);

		if (!chip->card_exist)
			turn_off_led(chip, LED_GPIO);
	}

	if (chip->need_reset) {
		dev_dbg(rtsx_dev(chip), "chip->need_reset = 0x%x\n",
			(unsigned int)(chip->need_reset));

		rtsx_reset_cards(chip);
	}

	if (chip->need_reinit) {
		dev_dbg(rtsx_dev(chip), "chip->need_reinit = 0x%x\n",
			(unsigned int)(chip->need_reinit));

		rtsx_reinit_cards(chip, 0);
	}
}