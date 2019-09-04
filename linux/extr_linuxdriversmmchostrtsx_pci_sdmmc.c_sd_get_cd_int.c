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
 int /*<<< orphan*/  RTSX_BIPR ; 
 int SD_EXIST ; 
 int rtsx_pci_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sd_get_cd_int(struct realtek_pci_sdmmc *host)
{
	return rtsx_pci_readl(host->pcr, RTSX_BIPR) & SD_EXIST;
}