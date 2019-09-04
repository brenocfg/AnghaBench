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
struct sge_txq {int /*<<< orphan*/  db_lock; scalar_t__ db_disabled; scalar_t__ db_pidx_inc; int /*<<< orphan*/  cntxt_id; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int PIDX_V (scalar_t__) ; 
 int QID_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SGE_PF_KDOORBELL_A ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void enable_txq_db(struct adapter *adap, struct sge_txq *q)
{
	spin_lock_irq(&q->db_lock);
	if (q->db_pidx_inc) {
		/* Make sure that all writes to the TX descriptors
		 * are committed before we tell HW about them.
		 */
		wmb();
		t4_write_reg(adap, MYPF_REG(SGE_PF_KDOORBELL_A),
			     QID_V(q->cntxt_id) | PIDX_V(q->db_pidx_inc));
		q->db_pidx_inc = 0;
	}
	q->db_disabled = 0;
	spin_unlock_irq(&q->db_lock);
}