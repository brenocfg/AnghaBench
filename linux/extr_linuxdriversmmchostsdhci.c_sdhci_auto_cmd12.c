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
struct sdhci_host {int flags; } ;
struct mmc_request {int /*<<< orphan*/  cap_cmd_during_tfr; int /*<<< orphan*/  sbc; } ;

/* Variables and functions */
 int SDHCI_AUTO_CMD12 ; 

__attribute__((used)) static inline bool sdhci_auto_cmd12(struct sdhci_host *host,
				    struct mmc_request *mrq)
{
	return !mrq->sbc && (host->flags & SDHCI_AUTO_CMD12) &&
	       !mrq->cap_cmd_during_tfr;
}