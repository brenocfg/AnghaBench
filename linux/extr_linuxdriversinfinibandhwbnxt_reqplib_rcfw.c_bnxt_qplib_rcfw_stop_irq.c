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
struct TYPE_2__ {int /*<<< orphan*/  max_elements; int /*<<< orphan*/  cons; } ;
struct bnxt_qplib_rcfw {int requested; int /*<<< orphan*/  vector; int /*<<< orphan*/  worker; TYPE_1__ creq; int /*<<< orphan*/  creq_bar_reg_iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREQ_DB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bnxt_qplib_rcfw*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void bnxt_qplib_rcfw_stop_irq(struct bnxt_qplib_rcfw *rcfw, bool kill)
{
	tasklet_disable(&rcfw->worker);
	/* Mask h/w interrupts */
	CREQ_DB(rcfw->creq_bar_reg_iomem, rcfw->creq.cons,
		rcfw->creq.max_elements);
	/* Sync with last running IRQ-handler */
	synchronize_irq(rcfw->vector);
	if (kill)
		tasklet_kill(&rcfw->worker);

	if (rcfw->requested) {
		free_irq(rcfw->vector, rcfw);
		rcfw->requested = false;
	}
}