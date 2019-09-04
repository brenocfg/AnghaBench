#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_hsmmc_host {TYPE_2__* mmc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ class_dev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mmc_detect_change (TYPE_2__*,int) ; 
 int /*<<< orphan*/  omap_hsmmc_protect_card (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static irqreturn_t omap_hsmmc_cover_irq(int irq, void *dev_id)
{
	struct omap_hsmmc_host *host = dev_id;

	sysfs_notify(&host->mmc->class_dev.kobj, NULL, "cover_switch");

	omap_hsmmc_protect_card(host);
	mmc_detect_change(host->mmc, (HZ * 200) / 1000);
	return IRQ_HANDLED;
}