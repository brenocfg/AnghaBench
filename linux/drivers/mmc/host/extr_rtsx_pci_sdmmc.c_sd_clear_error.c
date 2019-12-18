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
struct realtek_pci_sdmmc {int /*<<< orphan*/  pcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_STOP ; 
 int SD_CLR_ERR ; 
 int SD_STOP ; 
 int /*<<< orphan*/  rtsx_pci_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void sd_clear_error(struct realtek_pci_sdmmc *host)
{
	rtsx_pci_write_register(host->pcr, CARD_STOP,
			SD_STOP | SD_CLR_ERR, SD_STOP | SD_CLR_ERR);
}