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
struct realtek_pci_sdmmc {int cookie; int /*<<< orphan*/  mmc; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_detect_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct realtek_pci_sdmmc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void rtsx_pci_sdmmc_card_event(struct platform_device *pdev)
{
	struct realtek_pci_sdmmc *host = platform_get_drvdata(pdev);

	host->cookie = -1;
	mmc_detect_change(host->mmc, 0);
}