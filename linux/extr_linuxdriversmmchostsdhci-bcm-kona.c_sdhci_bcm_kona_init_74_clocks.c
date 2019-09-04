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
typedef  scalar_t__ u8 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ MMC_POWER_OFF ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sdhci_bcm_kona_init_74_clocks(struct sdhci_host *host,
				u8 power_mode)
{
	/*
	 *  JEDEC and SD spec specify supplying 74 continuous clocks to
	 * device after power up. With minimum bus (100KHz) that
	 * that translates to 740us
	 */
	if (power_mode != MMC_POWER_OFF)
		udelay(740);
}