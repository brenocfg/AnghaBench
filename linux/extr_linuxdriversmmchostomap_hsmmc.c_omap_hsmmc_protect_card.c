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
struct omap_hsmmc_host {int protect_card; int /*<<< orphan*/  mmc; int /*<<< orphan*/  dev; scalar_t__ (* get_cover_state ) (int /*<<< orphan*/ ) ;scalar_t__ reqs_blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_hsmmc_protect_card(struct omap_hsmmc_host *host)
{
	if (!host->get_cover_state)
		return;

	host->reqs_blocked = 0;
	if (host->get_cover_state(host->dev)) {
		if (host->protect_card) {
			dev_info(host->dev, "%s: cover is closed, "
					 "card is now accessible\n",
					 mmc_hostname(host->mmc));
			host->protect_card = 0;
		}
	} else {
		if (!host->protect_card) {
			dev_info(host->dev, "%s: cover is open, "
					 "card is now inaccessible\n",
					 mmc_hostname(host->mmc));
			host->protect_card = 1;
		}
	}
}