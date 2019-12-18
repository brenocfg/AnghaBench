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
struct TYPE_3__ {int /*<<< orphan*/  max_elements; int /*<<< orphan*/  cons; } ;
struct bnxt_qplib_rcfw {int requested; int vector; int /*<<< orphan*/  creq_ring_id; TYPE_1__ creq; int /*<<< orphan*/  creq_bar_reg_iomem; int /*<<< orphan*/  worker; TYPE_2__* res; } ;
struct TYPE_4__ {int /*<<< orphan*/  cctx; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  bnxt_qplib_creq_irq ; 
 int bnxt_qplib_is_chip_gen_p5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_qplib_ring_creq_db_rearm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnxt_qplib_service_creq ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct bnxt_qplib_rcfw*) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int bnxt_qplib_rcfw_start_irq(struct bnxt_qplib_rcfw *rcfw, int msix_vector,
			      bool need_init)
{
	bool gen_p5 = bnxt_qplib_is_chip_gen_p5(rcfw->res->cctx);
	int rc;

	if (rcfw->requested)
		return -EFAULT;

	rcfw->vector = msix_vector;
	if (need_init)
		tasklet_init(&rcfw->worker,
			     bnxt_qplib_service_creq, (unsigned long)rcfw);
	else
		tasklet_enable(&rcfw->worker);
	rc = request_irq(rcfw->vector, bnxt_qplib_creq_irq, 0,
			 "bnxt_qplib_creq", rcfw);
	if (rc)
		return rc;
	rcfw->requested = true;
	bnxt_qplib_ring_creq_db_rearm(rcfw->creq_bar_reg_iomem,
				      rcfw->creq.cons, rcfw->creq.max_elements,
				      rcfw->creq_ring_id, gen_p5);

	return 0;
}