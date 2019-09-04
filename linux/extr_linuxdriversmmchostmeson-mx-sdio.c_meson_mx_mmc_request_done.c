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
struct meson_mx_mmc_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/ * cmd; struct mmc_request* mrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 

__attribute__((used)) static void meson_mx_mmc_request_done(struct meson_mx_mmc_host *host)
{
	struct mmc_request *mrq;

	mrq = host->mrq;

	host->mrq = NULL;
	host->cmd = NULL;

	mmc_request_done(host->mmc, mrq);
}