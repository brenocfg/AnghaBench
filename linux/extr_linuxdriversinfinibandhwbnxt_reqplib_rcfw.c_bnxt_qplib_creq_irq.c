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
typedef  int /*<<< orphan*/  u32 ;
struct creq_base {int dummy; } ;
struct bnxt_qplib_hwq {scalar_t__ pbl_ptr; int /*<<< orphan*/  cons; } ;
struct bnxt_qplib_rcfw {int /*<<< orphan*/  worker; struct bnxt_qplib_hwq creq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HWQ_CMP (int /*<<< orphan*/ ,struct bnxt_qplib_hwq*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 size_t get_creq_idx (int /*<<< orphan*/ ) ; 
 size_t get_creq_pg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (struct creq_base*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bnxt_qplib_creq_irq(int irq, void *dev_instance)
{
	struct bnxt_qplib_rcfw *rcfw = dev_instance;
	struct bnxt_qplib_hwq *creq = &rcfw->creq;
	struct creq_base **creq_ptr;
	u32 sw_cons;

	/* Prefetch the CREQ element */
	sw_cons = HWQ_CMP(creq->cons, creq);
	creq_ptr = (struct creq_base **)rcfw->creq.pbl_ptr;
	prefetch(&creq_ptr[get_creq_pg(sw_cons)][get_creq_idx(sw_cons)]);

	tasklet_schedule(&rcfw->worker);

	return IRQ_HANDLED;
}