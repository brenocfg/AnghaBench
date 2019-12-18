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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sge_txq {scalar_t__ db_pidx; scalar_t__ size; int /*<<< orphan*/  db_lock; scalar_t__ db_pidx_inc; scalar_t__ db_disabled; scalar_t__ cntxt_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_WARN (struct adapter*,char*) ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int PIDX_T5_V (scalar_t__) ; 
 int PIDX_V (scalar_t__) ; 
 int QID_V (scalar_t__) ; 
 int /*<<< orphan*/  SGE_PF_KDOORBELL_A ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int read_eq_indices (struct adapter*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void sync_txq_pidx(struct adapter *adap, struct sge_txq *q)
{
	u16 hw_pidx, hw_cidx;
	int ret;

	spin_lock_irq(&q->db_lock);
	ret = read_eq_indices(adap, (u16)q->cntxt_id, &hw_pidx, &hw_cidx);
	if (ret)
		goto out;
	if (q->db_pidx != hw_pidx) {
		u16 delta;
		u32 val;

		if (q->db_pidx >= hw_pidx)
			delta = q->db_pidx - hw_pidx;
		else
			delta = q->size - hw_pidx + q->db_pidx;

		if (is_t4(adap->params.chip))
			val = PIDX_V(delta);
		else
			val = PIDX_T5_V(delta);
		wmb();
		t4_write_reg(adap, MYPF_REG(SGE_PF_KDOORBELL_A),
			     QID_V(q->cntxt_id) | val);
	}
out:
	q->db_disabled = 0;
	q->db_pidx_inc = 0;
	spin_unlock_irq(&q->db_lock);
	if (ret)
		CH_WARN(adap, "DB drop recovery failed.\n");
}