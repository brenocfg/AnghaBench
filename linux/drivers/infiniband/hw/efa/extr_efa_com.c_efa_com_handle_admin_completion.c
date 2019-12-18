#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u16 ;
struct TYPE_8__ {int /*<<< orphan*/  completed_cmd; } ;
struct TYPE_7__ {int /*<<< orphan*/  cc; } ;
struct TYPE_6__ {size_t cc; int phase; struct efa_admin_acq_entry* entries; } ;
struct efa_com_admin_queue {int depth; TYPE_4__ stats; TYPE_3__ sq; TYPE_2__ cq; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct efa_admin_acq_entry {TYPE_1__ acq_common_descriptor; } ;

/* Variables and functions */
 int EFA_ADMIN_ACQ_COMMON_DESC_PHASE_MASK ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_add (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  efa_com_handle_single_admin_completion (struct efa_com_admin_queue*,struct efa_admin_acq_entry*) ; 

__attribute__((used)) static void efa_com_handle_admin_completion(struct efa_com_admin_queue *aq)
{
	struct efa_admin_acq_entry *cqe;
	u16 queue_size_mask;
	u16 comp_num = 0;
	u8 phase;
	u16 ci;

	queue_size_mask = aq->depth - 1;

	ci = aq->cq.cc & queue_size_mask;
	phase = aq->cq.phase;

	cqe = &aq->cq.entries[ci];

	/* Go over all the completions */
	while ((READ_ONCE(cqe->acq_common_descriptor.flags) &
		EFA_ADMIN_ACQ_COMMON_DESC_PHASE_MASK) == phase) {
		/*
		 * Do not read the rest of the completion entry before the
		 * phase bit was validated
		 */
		dma_rmb();
		efa_com_handle_single_admin_completion(aq, cqe);

		ci++;
		comp_num++;
		if (ci == aq->depth) {
			ci = 0;
			phase = !phase;
		}

		cqe = &aq->cq.entries[ci];
	}

	aq->cq.cc += comp_num;
	aq->cq.phase = phase;
	aq->sq.cc += comp_num;
	atomic64_add(comp_num, &aq->stats.completed_cmd);
}