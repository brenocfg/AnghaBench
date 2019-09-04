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
typedef  int /*<<< orphan*/  u8 ;
struct rtsx_pcr {int dummy; } ;
struct realtek_pci_sdmmc {struct rtsx_pcr* pcr; } ;
struct mmc_command {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_CFG3 ; 
 int /*<<< orphan*/  SD_RSP_80CLK_TIMEOUT_EN ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_change_phase (struct realtek_pci_sdmmc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_clear_error (struct realtek_pci_sdmmc*) ; 
 int sd_read_data (struct realtek_pci_sdmmc*,struct mmc_command*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_wait_data_idle (struct realtek_pci_sdmmc*) ; 

__attribute__((used)) static int sd_tuning_rx_cmd(struct realtek_pci_sdmmc *host,
		u8 opcode, u8 sample_point)
{
	int err;
	struct mmc_command cmd = {};
	struct rtsx_pcr *pcr = host->pcr;

	sd_change_phase(host, sample_point, true);

	rtsx_pci_write_register(pcr, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
		SD_RSP_80CLK_TIMEOUT_EN);

	cmd.opcode = opcode;
	err = sd_read_data(host, &cmd, 0x40, NULL, 0, 100);
	if (err < 0) {
		/* Wait till SD DATA IDLE */
		sd_wait_data_idle(host);
		sd_clear_error(host);
		rtsx_pci_write_register(pcr, SD_CFG3,
			SD_RSP_80CLK_TIMEOUT_EN, 0);
		return err;
	}

	rtsx_pci_write_register(pcr, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN, 0);
	return 0;
}