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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int SDHCI_RESET_ALL ; 
 int /*<<< orphan*/  xenon_mask_cmd_conflict_err (struct sdhci_host*) ; 
 int /*<<< orphan*/  xenon_retune_setup (struct sdhci_host*) ; 
 int /*<<< orphan*/  xenon_set_acg (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  xenon_set_sdclk_off_idle (struct sdhci_host*,unsigned char,int) ; 

__attribute__((used)) static void xenon_reset_exit(struct sdhci_host *host,
			     unsigned char sdhc_id, u8 mask)
{
	/* Only SOFTWARE RESET ALL will clear the register setting */
	if (!(mask & SDHCI_RESET_ALL))
		return;

	/* Disable tuning request and auto-retuning again */
	xenon_retune_setup(host);

	xenon_set_acg(host, true);

	xenon_set_sdclk_off_idle(host, sdhc_id, false);

	xenon_mask_cmd_conflict_err(host);
}