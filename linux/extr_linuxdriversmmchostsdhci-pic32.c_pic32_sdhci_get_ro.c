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

__attribute__((used)) static unsigned int pic32_sdhci_get_ro(struct sdhci_host *host)
{
	/*
	 * The SDHCI_WRITE_PROTECT bit is unstable on current hardware so we
	 * can't depend on its value in any way.
	 */
	return 0;
}