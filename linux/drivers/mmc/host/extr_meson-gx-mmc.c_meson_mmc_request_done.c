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
struct mmc_request {int dummy; } ;
struct mmc_host {int dummy; } ;
struct meson_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 struct meson_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 

__attribute__((used)) static void meson_mmc_request_done(struct mmc_host *mmc,
				   struct mmc_request *mrq)
{
	struct meson_host *host = mmc_priv(mmc);

	host->cmd = NULL;
	mmc_request_done(host->mmc, mrq);
}