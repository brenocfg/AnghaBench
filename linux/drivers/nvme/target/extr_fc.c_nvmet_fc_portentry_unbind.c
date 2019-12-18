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
struct nvmet_fc_port_entry {int /*<<< orphan*/  pe_list; TYPE_1__* tgtport; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pe; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_fc_tgtlock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
nvmet_fc_portentry_unbind(struct nvmet_fc_port_entry *pe)
{
	unsigned long flags;

	spin_lock_irqsave(&nvmet_fc_tgtlock, flags);
	if (pe->tgtport)
		pe->tgtport->pe = NULL;
	list_del(&pe->pe_list);
	spin_unlock_irqrestore(&nvmet_fc_tgtlock, flags);
}