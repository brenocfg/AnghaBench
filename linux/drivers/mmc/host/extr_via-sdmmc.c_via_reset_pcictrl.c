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
struct via_crdr_mmc_host {scalar_t__ power; int /*<<< orphan*/  lock; scalar_t__ pcictrl_mmiobase; } ;

/* Variables and functions */
 scalar_t__ MMC_VDD_165_195 ; 
 scalar_t__ VIA_CRDR_PCICLKGATT ; 
 int /*<<< orphan*/  VIA_CRDR_PCICLKGATT_3V3 ; 
 int /*<<< orphan*/  VIA_CRDR_PCICLKGATT_PAD_PWRON ; 
 int /*<<< orphan*/  VIA_CRDR_PCICLKGATT_SFTRST ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  via_pwron_sleep (struct via_crdr_mmc_host*) ; 
 int /*<<< orphan*/  via_restore_pcictrlreg (struct via_crdr_mmc_host*) ; 
 int /*<<< orphan*/  via_restore_sdcreg (struct via_crdr_mmc_host*) ; 
 int /*<<< orphan*/  via_save_pcictrlreg (struct via_crdr_mmc_host*) ; 
 int /*<<< orphan*/  via_save_sdcreg (struct via_crdr_mmc_host*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void via_reset_pcictrl(struct via_crdr_mmc_host *host)
{
	unsigned long flags;
	u8 gatt;

	spin_lock_irqsave(&host->lock, flags);

	via_save_pcictrlreg(host);
	via_save_sdcreg(host);

	spin_unlock_irqrestore(&host->lock, flags);

	gatt = VIA_CRDR_PCICLKGATT_PAD_PWRON;
	if (host->power == MMC_VDD_165_195)
		gatt &= VIA_CRDR_PCICLKGATT_3V3;
	else
		gatt |= VIA_CRDR_PCICLKGATT_3V3;
	writeb(gatt, host->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	via_pwron_sleep(host);
	gatt |= VIA_CRDR_PCICLKGATT_SFTRST;
	writeb(gatt, host->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	msleep(3);

	spin_lock_irqsave(&host->lock, flags);

	via_restore_pcictrlreg(host);
	via_restore_sdcreg(host);

	spin_unlock_irqrestore(&host->lock, flags);
}