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
struct rtsx_pcr {int dummy; } ;
struct realtek_pci_sdmmc {struct rtsx_pcr* pcr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SD_BUS_STAT ; 
 int /*<<< orphan*/  SD_CLK_FORCE_STOP ; 
 int SD_CMD_STATUS ; 
 int SD_DAT0_STATUS ; 
 int SD_DAT1_STATUS ; 
 int SD_DAT2_STATUS ; 
 int SD_DAT3_STATUS ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtsx_pci_read_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int*) ; 
 int rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_wait_voltage_stable_1(struct realtek_pci_sdmmc *host)
{
	struct rtsx_pcr *pcr = host->pcr;
	int err;
	u8 stat;

	/* Reference to Signal Voltage Switch Sequence in SD spec.
	 * Wait for a period of time so that the card can drive SD_CMD and
	 * SD_DAT[3:0] to low after sending back CMD11 response.
	 */
	mdelay(1);

	/* SD_CMD, SD_DAT[3:0] should be driven to low by card;
	 * If either one of SD_CMD,SD_DAT[3:0] is not low,
	 * abort the voltage switch sequence;
	 */
	err = rtsx_pci_read_register(pcr, SD_BUS_STAT, &stat);
	if (err < 0)
		return err;

	if (stat & (SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
				SD_DAT1_STATUS | SD_DAT0_STATUS))
		return -EINVAL;

	/* Stop toggle SD clock */
	err = rtsx_pci_write_register(pcr, SD_BUS_STAT,
			0xFF, SD_CLK_FORCE_STOP);
	if (err < 0)
		return err;

	return 0;
}