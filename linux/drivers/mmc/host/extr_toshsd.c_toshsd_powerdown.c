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
struct toshsd_host {int /*<<< orphan*/  pdev; scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ SDIO_BASE ; 
 scalar_t__ SDIO_CLOCKNWAITCTRL ; 
 scalar_t__ SD_CARDCLOCKCTRL ; 
 scalar_t__ SD_INTMASKCARD ; 
 int /*<<< orphan*/  SD_PCICFG_CLKSTOP ; 
 int /*<<< orphan*/  SD_PCICFG_POWER1 ; 
 int /*<<< orphan*/  SD_PCICFG_PWR1_OFF ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toshsd_powerdown(struct toshsd_host *host)
{
	/* mask all interrupts */
	iowrite32(0xffffffff, host->ioaddr + SD_INTMASKCARD);
	/* disable card clock */
	iowrite16(0x000, host->ioaddr + SDIO_BASE + SDIO_CLOCKNWAITCTRL);
	iowrite16(0, host->ioaddr + SD_CARDCLOCKCTRL);
	/* power down card */
	pci_write_config_byte(host->pdev, SD_PCICFG_POWER1, SD_PCICFG_PWR1_OFF);
	/* disable clock */
	pci_write_config_byte(host->pdev, SD_PCICFG_CLKSTOP, 0);
}