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
struct rvt_qp {int s_flags; scalar_t__ priv; int /*<<< orphan*/  s_lock; } ;
struct hfi1_qp_priv {int /*<<< orphan*/  s_iowait; } ;

/* Variables and functions */
 int HFI1_S_ANY_WAIT_IO ; 
 int /*<<< orphan*/  IOWAIT_PENDING_IB ; 
 int /*<<< orphan*/  _hfi1_schedule_send (struct rvt_qp*) ; 
 scalar_t__ hfi1_send_ok (struct rvt_qp*) ; 
 int /*<<< orphan*/  iowait_set_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

bool hfi1_schedule_send(struct rvt_qp *qp)
{
	lockdep_assert_held(&qp->s_lock);
	if (hfi1_send_ok(qp)) {
		_hfi1_schedule_send(qp);
		return true;
	}
	if (qp->s_flags & HFI1_S_ANY_WAIT_IO)
		iowait_set_flag(&((struct hfi1_qp_priv *)qp->priv)->s_iowait,
				IOWAIT_PENDING_IB);
	return false;
}