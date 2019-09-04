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
struct sge_fl {int pend_cred; int /*<<< orphan*/ * bar2_addr; int /*<<< orphan*/  bar2_qid; int /*<<< orphan*/  cntxt_id; } ;
struct TYPE_3__ {int sge_fl_db; } ;
struct TYPE_4__ {int /*<<< orphan*/  chip; TYPE_1__ arch; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int FL_PER_EQ_UNIT ; 
 int PIDX_T5_V (int) ; 
 int PIDX_V (int) ; 
 int QID_V (int /*<<< orphan*/ ) ; 
 int SGE_UDB_KDOORBELL ; 
 scalar_t__ SGE_VF_KDOORBELL ; 
 scalar_t__ T4VF_SGE_BASE_ADDR ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,scalar_t__,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ring_fl_db(struct adapter *adapter, struct sge_fl *fl)
{
	u32 val = adapter->params.arch.sge_fl_db;

	/* The SGE keeps track of its Producer and Consumer Indices in terms
	 * of Egress Queue Units so we can only tell it about integral numbers
	 * of multiples of Free List Entries per Egress Queue Units ...
	 */
	if (fl->pend_cred >= FL_PER_EQ_UNIT) {
		if (is_t4(adapter->params.chip))
			val |= PIDX_V(fl->pend_cred / FL_PER_EQ_UNIT);
		else
			val |= PIDX_T5_V(fl->pend_cred / FL_PER_EQ_UNIT);

		/* Make sure all memory writes to the Free List queue are
		 * committed before we tell the hardware about them.
		 */
		wmb();

		/* If we don't have access to the new User Doorbell (T5+), use
		 * the old doorbell mechanism; otherwise use the new BAR2
		 * mechanism.
		 */
		if (unlikely(fl->bar2_addr == NULL)) {
			t4_write_reg(adapter,
				     T4VF_SGE_BASE_ADDR + SGE_VF_KDOORBELL,
				     QID_V(fl->cntxt_id) | val);
		} else {
			writel(val | QID_V(fl->bar2_qid),
			       fl->bar2_addr + SGE_UDB_KDOORBELL);

			/* This Write memory Barrier will force the write to
			 * the User Doorbell area to be flushed.
			 */
			wmb();
		}
		fl->pend_cred %= FL_PER_EQ_UNIT;
	}
}