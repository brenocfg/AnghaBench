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
struct realtek_pci_sdmmc {int /*<<< orphan*/  pcr; } ;

/* Variables and functions */
 int SD_DATA_IDLE ; 
 int /*<<< orphan*/  SD_DATA_STATE ; 
 int rtsx_pci_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sd_wait_data_idle(struct realtek_pci_sdmmc *host)
{
	int err, i;
	u8 val = 0;

	for (i = 0; i < 100; i++) {
		err = rtsx_pci_read_register(host->pcr, SD_DATA_STATE, &val);
		if (val & SD_DATA_IDLE)
			return;

		udelay(100);
	}
}