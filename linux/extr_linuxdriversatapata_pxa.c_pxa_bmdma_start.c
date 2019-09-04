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
struct pata_pxa_data {int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  dma_done; } ;
struct ata_queued_cmd {TYPE_1__* ap; } ;
struct TYPE_2__ {struct pata_pxa_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pxa_bmdma_start(struct ata_queued_cmd *qc)
{
	struct pata_pxa_data *pd = qc->ap->private_data;
	init_completion(&pd->dma_done);
	dma_async_issue_pending(pd->dma_chan);
}