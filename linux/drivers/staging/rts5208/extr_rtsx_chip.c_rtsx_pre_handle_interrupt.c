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
typedef  int u32 ;
struct rtsx_chip {int int_reg; int ocp_int; scalar_t__ sd_io; int /*<<< orphan*/  need_reinit; int /*<<< orphan*/  need_reset; scalar_t__ ms_show_cnt; scalar_t__ ms_reset_counter; int /*<<< orphan*/  need_release; scalar_t__ xd_show_cnt; scalar_t__ xd_reset_counter; scalar_t__ sd_show_cnt; scalar_t__ sd_reset_counter; scalar_t__ auto_delink_cnt; scalar_t__ ss_counter; scalar_t__ ss_en; } ;

/* Variables and functions */
 int CARD_INT ; 
 scalar_t__ CHECK_BARO_PKG (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_PID (struct rtsx_chip*,int) ; 
 int DATA_DONE_INT ; 
 int MS_EXIST ; 
 int MS_INT ; 
 int /*<<< orphan*/  MS_NR ; 
 int OC_INT ; 
 int /*<<< orphan*/  QFN ; 
 int /*<<< orphan*/  RTSX_BIER ; 
 int /*<<< orphan*/  RTSX_BIPR ; 
 int /*<<< orphan*/  RTSX_STAT_RUN ; 
 scalar_t__ RTSX_STAT_SS ; 
 int SD_EXIST ; 
 int SD_INT ; 
 int /*<<< orphan*/  SD_NR ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int XD_EXIST ; 
 int XD_INT ; 
 int /*<<< orphan*/  XD_NR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtsx_exit_L1 (struct rtsx_chip*) ; 
 scalar_t__ rtsx_get_stat (struct rtsx_chip*) ; 
 void* rtsx_readl (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rtsx_pre_handle_interrupt(struct rtsx_chip *chip)
{
	u32 status, int_enable;
	bool exit_ss = false;
#ifdef SUPPORT_OCP
	u32 ocp_int = 0;

	ocp_int = OC_INT;
#endif

	if (chip->ss_en) {
		chip->ss_counter = 0;
		if (rtsx_get_stat(chip) == RTSX_STAT_SS) {
			exit_ss = true;
			rtsx_exit_L1(chip);
			rtsx_set_stat(chip, RTSX_STAT_RUN);
		}
	}

	int_enable = rtsx_readl(chip, RTSX_BIER);
	chip->int_reg = rtsx_readl(chip, RTSX_BIPR);

	if (((chip->int_reg & int_enable) == 0) ||
	    (chip->int_reg == 0xFFFFFFFF))
		return STATUS_FAIL;

	status = chip->int_reg &= (int_enable | 0x7FFFFF);

	if (status & CARD_INT) {
		chip->auto_delink_cnt = 0;

		if (status & SD_INT) {
			if (status & SD_EXIST) {
				set_bit(SD_NR, &chip->need_reset);
			} else {
				set_bit(SD_NR, &chip->need_release);
				chip->sd_reset_counter = 0;
				chip->sd_show_cnt = 0;
				clear_bit(SD_NR, &chip->need_reset);
			}
		} else {
			/*
			 * If multi-luns, it's possible that
			 * when plugging/unplugging one card
			 * there is another card which still
			 * exists in the slot. In this case,
			 * all existed cards should be reset.
			 */
			if (exit_ss && (status & SD_EXIST))
				set_bit(SD_NR, &chip->need_reinit);
		}
		if (!CHECK_PID(chip, 0x5288) || CHECK_BARO_PKG(chip, QFN)) {
			if (status & XD_INT) {
				if (status & XD_EXIST) {
					set_bit(XD_NR, &chip->need_reset);
				} else {
					set_bit(XD_NR, &chip->need_release);
					chip->xd_reset_counter = 0;
					chip->xd_show_cnt = 0;
					clear_bit(XD_NR, &chip->need_reset);
				}
			} else {
				if (exit_ss && (status & XD_EXIST))
					set_bit(XD_NR, &chip->need_reinit);
			}
		}
		if (status & MS_INT) {
			if (status & MS_EXIST) {
				set_bit(MS_NR, &chip->need_reset);
			} else {
				set_bit(MS_NR, &chip->need_release);
				chip->ms_reset_counter = 0;
				chip->ms_show_cnt = 0;
				clear_bit(MS_NR, &chip->need_reset);
			}
		} else {
			if (exit_ss && (status & MS_EXIST))
				set_bit(MS_NR, &chip->need_reinit);
		}
	}

#ifdef SUPPORT_OCP
	chip->ocp_int = ocp_int & status;
#endif

	if (chip->sd_io && (chip->int_reg & DATA_DONE_INT))
		chip->int_reg &= ~(u32)DATA_DONE_INT;

	return STATUS_SUCCESS;
}