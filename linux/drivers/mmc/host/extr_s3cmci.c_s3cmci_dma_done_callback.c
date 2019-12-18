#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s3cmci_host {int dma_complete; int /*<<< orphan*/  complete_lock; int /*<<< orphan*/  pio_tasklet; int /*<<< orphan*/  complete_what; TYPE_1__* mrq; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  COMPLETION_FINALIZE ; 
 int /*<<< orphan*/  dbg (struct s3cmci_host*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dbg_dma ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s3cmci_dma_done_callback(void *arg)
{
	struct s3cmci_host *host = arg;
	unsigned long iflags;

	BUG_ON(!host->mrq);
	BUG_ON(!host->mrq->data);

	spin_lock_irqsave(&host->complete_lock, iflags);

	dbg(host, dbg_dma, "DMA FINISHED\n");

	host->dma_complete = 1;
	host->complete_what = COMPLETION_FINALIZE;

	tasklet_schedule(&host->pio_tasklet);
	spin_unlock_irqrestore(&host->complete_lock, iflags);

}