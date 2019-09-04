#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bcm2835_host {TYPE_1__* mmc; scalar_t__ clock; int /*<<< orphan*/  hcfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  ios; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCFG_BUSY_IRPT_EN ; 
 int /*<<< orphan*/  bcm2835_sdhost_reset_internal (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_set_ios (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static void bcm2835_sdhost_init(struct bcm2835_host *host, int soft)
{
	pr_debug("bcm2835_sdhost_init(%d)\n", soft);

	/* Set interrupt enables */
	host->hcfg = SDHCFG_BUSY_IRPT_EN;

	bcm2835_sdhost_reset_internal(host);

	if (soft) {
		/* force clock reconfiguration */
		host->clock = 0;
		bcm2835_sdhost_set_ios(host->mmc, &host->mmc->ios);
	}
}