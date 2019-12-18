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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_PULL_CTL1 ; 
 int /*<<< orphan*/  CARD_PULL_CTL2 ; 
 int /*<<< orphan*/  CARD_PULL_CTL3 ; 
 int /*<<< orphan*/  CARD_PULL_CTL4 ; 
 int /*<<< orphan*/  CARD_PULL_CTL5 ; 
 int /*<<< orphan*/  CARD_PULL_CTL6 ; 
 scalar_t__ CHECK_BARO_PKG (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 scalar_t__ CHECK_PID (struct rtsx_chip*,int) ; 
 int MS_BS_NP ; 
 int /*<<< orphan*/  MS_CARD ; 
 int MS_CLK_NP ; 
 int MS_D0_PD ; 
 int MS_D1_PD ; 
 int MS_D2_PD ; 
 int MS_D3_PD ; 
 int MS_D4_PD ; 
 int MS_D5_PD ; 
 int MS_D6_PD ; 
 int MS_D7_PD ; 
 int MS_INS_PU ; 
 int /*<<< orphan*/  QFN ; 
 int SD_CD_PU ; 
 int SD_CMD_PD ; 
 int SD_D2_PD ; 
 int SD_D3_PD ; 
 int SD_WP_PD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int XD_ALE_PD ; 
 int XD_CD_PU ; 
 int XD_CE_PD ; 
 int XD_CLE_PD ; 
 int XD_D4_PD ; 
 int XD_RDY_PD ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ms_pull_ctl_enable(struct rtsx_chip *chip)
{
	int retval;

	rtsx_init_cmd(chip);

	if (CHECK_PID(chip, 0x5208)) {
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF,
			     MS_D1_PD | MS_D2_PD | MS_CLK_NP | MS_D6_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF,
			     MS_D3_PD | MS_D0_PD | MS_BS_NP | XD_D4_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF,
			     MS_D7_PD | XD_CE_PD | XD_CLE_PD | XD_CD_PU);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF,
			     XD_RDY_PD | SD_D3_PD | SD_D2_PD | XD_ALE_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL5, 0xFF,
			     MS_INS_PU | SD_WP_PD | SD_CD_PU | SD_CMD_PD);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_PULL_CTL6, 0xFF,
			     MS_D5_PD | MS_D4_PD);
	} else if (CHECK_PID(chip, 0x5288)) {
		if (CHECK_BARO_PKG(chip, QFN)) {
			rtsx_add_cmd(chip, WRITE_REG_CMD,
				     CARD_PULL_CTL1, 0xFF, 0x55);
			rtsx_add_cmd(chip, WRITE_REG_CMD,
				     CARD_PULL_CTL2, 0xFF, 0x45);
			rtsx_add_cmd(chip, WRITE_REG_CMD,
				     CARD_PULL_CTL3, 0xFF, 0x4B);
			rtsx_add_cmd(chip, WRITE_REG_CMD,
				     CARD_PULL_CTL4, 0xFF, 0x29);
		}
	}

	retval = rtsx_send_cmd(chip, MS_CARD, 100);
	if (retval < 0)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}