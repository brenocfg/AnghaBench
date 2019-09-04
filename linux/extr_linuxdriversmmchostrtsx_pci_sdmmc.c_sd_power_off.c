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
struct rtsx_pcr {int dummy; } ;
struct realtek_pci_sdmmc {int /*<<< orphan*/  power_state; struct rtsx_pcr* pcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_CLK_EN ; 
 int /*<<< orphan*/  CARD_OE ; 
 int /*<<< orphan*/  RTSX_SD_CARD ; 
 int /*<<< orphan*/  SDMMC_POWER_OFF ; 
 int /*<<< orphan*/  SD_CLK_EN ; 
 int /*<<< orphan*/  SD_OUTPUT_EN ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtsx_pci_card_power_off (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int rtsx_pci_card_pull_ctl_disable (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int) ; 

__attribute__((used)) static int sd_power_off(struct realtek_pci_sdmmc *host)
{
	struct rtsx_pcr *pcr = host->pcr;
	int err;

	host->power_state = SDMMC_POWER_OFF;

	rtsx_pci_init_cmd(pcr);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_CLK_EN, SD_CLK_EN, 0);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_OE, SD_OUTPUT_EN, 0);

	err = rtsx_pci_send_cmd(pcr, 100);
	if (err < 0)
		return err;

	err = rtsx_pci_card_power_off(pcr, RTSX_SD_CARD);
	if (err < 0)
		return err;

	return rtsx_pci_card_pull_ctl_disable(pcr, RTSX_SD_CARD);
}