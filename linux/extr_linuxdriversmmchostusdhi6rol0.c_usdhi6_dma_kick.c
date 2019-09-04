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
struct usdhi6_host {int /*<<< orphan*/  chan_tx; int /*<<< orphan*/  chan_rx; TYPE_2__* mrq; } ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usdhi6_dma_kick(struct usdhi6_host *host)
{
	if (host->mrq->data->flags & MMC_DATA_READ)
		dma_async_issue_pending(host->chan_rx);
	else
		dma_async_issue_pending(host->chan_tx);
}