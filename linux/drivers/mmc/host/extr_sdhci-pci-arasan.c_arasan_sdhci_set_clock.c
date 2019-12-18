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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arasan_select_phy_clock (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_set_clock (struct sdhci_host*,unsigned int) ; 

__attribute__((used)) static void arasan_sdhci_set_clock(struct sdhci_host *host, unsigned int clock)
{
	sdhci_set_clock(host, clock);

	/* Change phy settings for the new clock */
	arasan_select_phy_clock(host);
}