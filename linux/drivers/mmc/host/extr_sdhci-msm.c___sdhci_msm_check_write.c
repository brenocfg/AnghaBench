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
typedef  int u16 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_msm_host {int transfer_mode; scalar_t__ pwr_irq_flag; int /*<<< orphan*/  use_cdr; } ;
struct sdhci_host {int /*<<< orphan*/  pwr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_SEND_TUNING_BLOCK ; 
 int /*<<< orphan*/  MMC_SEND_TUNING_BLOCK_HS200 ; 
 int REQ_BUS_OFF ; 
 int REQ_BUS_ON ; 
 int REQ_IO_HIGH ; 
 int REQ_IO_LOW ; 
#define  SDHCI_COMMAND 132 
 int SDHCI_CTRL_VDD_180 ; 
 int /*<<< orphan*/  SDHCI_GET_CMD (int) ; 
#define  SDHCI_HOST_CONTROL2 131 
#define  SDHCI_POWER_CONTROL 130 
 int SDHCI_RESET_ALL ; 
#define  SDHCI_SOFTWARE_RESET 129 
#define  SDHCI_TRANSFER_MODE 128 
 int SDHCI_TRNS_READ ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  sdhci_msm_set_cdr (struct sdhci_host*,int) ; 
 struct sdhci_msm_host* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static int __sdhci_msm_check_write(struct sdhci_host *host, u16 val, int reg)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	u32 req_type = 0;

	switch (reg) {
	case SDHCI_HOST_CONTROL2:
		req_type = (val & SDHCI_CTRL_VDD_180) ? REQ_IO_LOW :
			REQ_IO_HIGH;
		break;
	case SDHCI_SOFTWARE_RESET:
		if (host->pwr && (val & SDHCI_RESET_ALL))
			req_type = REQ_BUS_OFF;
		break;
	case SDHCI_POWER_CONTROL:
		req_type = !val ? REQ_BUS_OFF : REQ_BUS_ON;
		break;
	case SDHCI_TRANSFER_MODE:
		msm_host->transfer_mode = val;
		break;
	case SDHCI_COMMAND:
		if (!msm_host->use_cdr)
			break;
		if ((msm_host->transfer_mode & SDHCI_TRNS_READ) &&
		    SDHCI_GET_CMD(val) != MMC_SEND_TUNING_BLOCK_HS200 &&
		    SDHCI_GET_CMD(val) != MMC_SEND_TUNING_BLOCK)
			sdhci_msm_set_cdr(host, true);
		else
			sdhci_msm_set_cdr(host, false);
		break;
	}

	if (req_type) {
		msm_host->pwr_irq_flag = 0;
		/*
		 * Since this register write may trigger a power irq, ensure
		 * all previous register writes are complete by this point.
		 */
		mb();
	}
	return req_type;
}