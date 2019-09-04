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
 int /*<<< orphan*/  sdhci_request_done (struct sdhci_host*) ; 

__attribute__((used)) static void sdhci_tasklet_finish(unsigned long param)
{
	struct sdhci_host *host = (struct sdhci_host *)param;

	while (!sdhci_request_done(host))
		;
}