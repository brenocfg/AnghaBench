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
struct TYPE_4__ {int sge_fl_db; } ;
struct TYPE_3__ {int /*<<< orphan*/  chip; TYPE_2__ arch; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int PIDX_T5_V (int) ; 
 int PIDX_V (int) ; 
 int QID_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SGE_PF_KDOORBELL_A ; 
 int SGE_UDB_KDOORBELL ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ring_fl_db(struct adapter *adap, struct sge_fl *q)
{
	if (q->pend_cred >= 8) {
		u32 val = adap->params.arch.sge_fl_db;

		if (is_t4(adap->params.chip))
			val |= PIDX_V(q->pend_cred / 8);
		else
			val |= PIDX_T5_V(q->pend_cred / 8);

		/* Make sure all memory writes to the Free List queue are
		 * committed before we tell the hardware about them.
		 */
		wmb();

		/* If we don't have access to the new User Doorbell (T5+), use
		 * the old doorbell mechanism; otherwise use the new BAR2
		 * mechanism.
		 */
		if (unlikely(q->bar2_addr == NULL)) {
			t4_write_reg(adap, MYPF_REG(SGE_PF_KDOORBELL_A),
				     val | QID_V(q->cntxt_id));
		} else {
			writel(val | QID_V(q->bar2_qid),
			       q->bar2_addr + SGE_UDB_KDOORBELL);

			/* This Write memory Barrier will force the write to
			 * the User Doorbell area to be flushed.
			 */
			wmb();
		}
		q->pend_cred &= 7;
	}
}