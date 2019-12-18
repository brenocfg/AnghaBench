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
struct TYPE_4__ {int /*<<< orphan*/  max_elements; int /*<<< orphan*/  cons; } ;
struct bnxt_qplib_rcfw {int requested; int /*<<< orphan*/  vector; int /*<<< orphan*/  worker; int /*<<< orphan*/  creq_ring_id; TYPE_2__ creq; int /*<<< orphan*/  creq_bar_reg_iomem; TYPE_1__* res; } ;
struct TYPE_3__ {int /*<<< orphan*/  cctx; } ;

/* Variables and functions */
 int bnxt_qplib_is_chip_gen_p5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_qplib_ring_creq_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bnxt_qplib_rcfw*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void bnxt_qplib_rcfw_stop_irq(struct bnxt_qplib_rcfw *rcfw, bool kill)
{
	bool gen_p5 = bnxt_qplib_is_chip_gen_p5(rcfw->res->cctx);

	tasklet_disable(&rcfw->worker);
	/* Mask h/w interrupts */
	bnxt_qplib_ring_creq_db(rcfw->creq_bar_reg_iomem, rcfw->creq.cons,
				rcfw->creq.max_elements, rcfw->creq_ring_id,
				gen_p5);
	/* Sync with last running IRQ-handler */
	synchronize_irq(rcfw->vector);
	if (kill)
		tasklet_kill(&rcfw->worker);

	if (rcfw->requested) {
		free_irq(rcfw->vector, rcfw);
		rcfw->requested = false;
	}
}