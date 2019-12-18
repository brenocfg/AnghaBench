#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtsx_pcr {TYPE_1__* slots; } ;
struct realtek_pci_sdmmc {int cookie; int /*<<< orphan*/  host_mutex; int /*<<< orphan*/  work; int /*<<< orphan*/  power_state; struct platform_device* pdev; struct mmc_host* mmc; struct rtsx_pcr* pcr; } ;
struct TYPE_5__ {struct pcr_handle* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct pcr_handle {struct rtsx_pcr* pcr; } ;
struct mmc_host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  card_event; struct platform_device* p_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t RTSX_SD_CARD ; 
 int /*<<< orphan*/  SDMMC_POWER_OFF ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,TYPE_2__*) ; 
 struct realtek_pci_sdmmc* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct realtek_pci_sdmmc*) ; 
 int /*<<< orphan*/  realtek_init_host (struct realtek_pci_sdmmc*) ; 
 int /*<<< orphan*/  rtsx_pci_sdmmc_card_event ; 
 int /*<<< orphan*/  sd_request ; 

__attribute__((used)) static int rtsx_pci_sdmmc_drv_probe(struct platform_device *pdev)
{
	struct mmc_host *mmc;
	struct realtek_pci_sdmmc *host;
	struct rtsx_pcr *pcr;
	struct pcr_handle *handle = pdev->dev.platform_data;

	if (!handle)
		return -ENXIO;

	pcr = handle->pcr;
	if (!pcr)
		return -ENXIO;

	dev_dbg(&(pdev->dev), ": Realtek PCI-E SDMMC controller found\n");

	mmc = mmc_alloc_host(sizeof(*host), &pdev->dev);
	if (!mmc)
		return -ENOMEM;

	host = mmc_priv(mmc);
	host->pcr = pcr;
	host->mmc = mmc;
	host->pdev = pdev;
	host->cookie = -1;
	host->power_state = SDMMC_POWER_OFF;
	INIT_WORK(&host->work, sd_request);
	platform_set_drvdata(pdev, host);
	pcr->slots[RTSX_SD_CARD].p_dev = pdev;
	pcr->slots[RTSX_SD_CARD].card_event = rtsx_pci_sdmmc_card_event;

	mutex_init(&host->host_mutex);

	realtek_init_host(host);

	mmc_add_host(mmc);

	return 0;
}