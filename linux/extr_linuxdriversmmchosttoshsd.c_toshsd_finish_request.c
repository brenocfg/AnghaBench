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
struct toshsd_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/ * data; int /*<<< orphan*/ * cmd; struct mmc_request* mrq; } ;
struct mmc_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  toshsd_set_led (struct toshsd_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toshsd_finish_request(struct toshsd_host *host)
{
	struct mmc_request *mrq = host->mrq;

	/* Write something to end the command */
	host->mrq = NULL;
	host->cmd = NULL;
	host->data = NULL;

	toshsd_set_led(host, 0);
	mmc_request_done(host->mmc, mrq);
}