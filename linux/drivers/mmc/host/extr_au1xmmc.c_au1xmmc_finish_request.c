#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmc_request {int dummy; } ;
struct TYPE_4__ {scalar_t__ len; scalar_t__ offset; scalar_t__ index; } ;
struct TYPE_3__ {scalar_t__ dir; scalar_t__ len; } ;
struct au1xmmc_host {int flags; int /*<<< orphan*/  mmc; int /*<<< orphan*/  status; TYPE_2__ pio; TYPE_1__ dma; struct mmc_request* mrq; } ;

/* Variables and functions */
 int HOST_F_ACTIVE ; 
 int HOST_F_DMA ; 
 int /*<<< orphan*/  HOST_S_IDLE ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 

__attribute__((used)) static void au1xmmc_finish_request(struct au1xmmc_host *host)
{
	struct mmc_request *mrq = host->mrq;

	host->mrq = NULL;
	host->flags &= HOST_F_ACTIVE | HOST_F_DMA;

	host->dma.len = 0;
	host->dma.dir = 0;

	host->pio.index  = 0;
	host->pio.offset = 0;
	host->pio.len = 0;

	host->status = HOST_S_IDLE;

	mmc_request_done(host->mmc, mrq);
}