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
struct pdc_state {int /*<<< orphan*/  pdc_idx; TYPE_1__* pdev; } ;
struct mbox_chan {struct pdc_state* con_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_ring_free (struct pdc_state*) ; 

__attribute__((used)) static void pdc_shutdown(struct mbox_chan *chan)
{
	struct pdc_state *pdcs = chan->con_priv;

	if (!pdcs)
		return;

	dev_dbg(&pdcs->pdev->dev,
		"Shutdown mailbox channel for PDC %u", pdcs->pdc_idx);
	pdc_ring_free(pdcs);
}