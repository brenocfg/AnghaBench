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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  isr_count; int /*<<< orphan*/  last_isr_time; } ;
struct TYPE_4__ {TYPE_1__ misc_stats; } ;
struct fnic {int /*<<< orphan*/ * intr; TYPE_2__ fnic_stats; int /*<<< orphan*/  legacy_pba; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FNIC_INTX_ERR ; 
 int FNIC_INTX_NOTIFY ; 
 int FNIC_INTX_WQ_RQ_COPYWQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnic_handle_link_event (struct fnic*) ; 
 int /*<<< orphan*/  fnic_log_q_error (struct fnic*) ; 
 scalar_t__ fnic_rq_cmpl_handler (struct fnic*,int) ; 
 scalar_t__ fnic_wq_cmpl_handler (struct fnic*,int) ; 
 scalar_t__ fnic_wq_copy_cmpl_handler (struct fnic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_completions ; 
 int /*<<< orphan*/  jiffies ; 
 int vnic_intr_legacy_pba (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_intr_return_all_credits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_return_credits (int /*<<< orphan*/ *,unsigned long,int,int) ; 

__attribute__((used)) static irqreturn_t fnic_isr_legacy(int irq, void *data)
{
	struct fnic *fnic = data;
	u32 pba;
	unsigned long work_done = 0;

	pba = vnic_intr_legacy_pba(fnic->legacy_pba);
	if (!pba)
		return IRQ_NONE;

	fnic->fnic_stats.misc_stats.last_isr_time = jiffies;
	atomic64_inc(&fnic->fnic_stats.misc_stats.isr_count);

	if (pba & (1 << FNIC_INTX_NOTIFY)) {
		vnic_intr_return_all_credits(&fnic->intr[FNIC_INTX_NOTIFY]);
		fnic_handle_link_event(fnic);
	}

	if (pba & (1 << FNIC_INTX_ERR)) {
		vnic_intr_return_all_credits(&fnic->intr[FNIC_INTX_ERR]);
		fnic_log_q_error(fnic);
	}

	if (pba & (1 << FNIC_INTX_WQ_RQ_COPYWQ)) {
		work_done += fnic_wq_copy_cmpl_handler(fnic, io_completions);
		work_done += fnic_wq_cmpl_handler(fnic, -1);
		work_done += fnic_rq_cmpl_handler(fnic, -1);

		vnic_intr_return_credits(&fnic->intr[FNIC_INTX_WQ_RQ_COPYWQ],
					 work_done,
					 1 /* unmask intr */,
					 1 /* reset intr timer */);
	}

	return IRQ_HANDLED;
}