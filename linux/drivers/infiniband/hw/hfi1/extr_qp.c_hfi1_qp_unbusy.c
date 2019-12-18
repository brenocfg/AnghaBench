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
struct rvt_qp {int s_flags; struct hfi1_qp_priv* priv; } ;
struct iowait_work {int dummy; } ;
struct hfi1_qp_priv {int s_flags; int /*<<< orphan*/  s_iowait; } ;

/* Variables and functions */
 int HFI1_S_TID_BUSY_SET ; 
 scalar_t__ IOWAIT_IB_SE ; 
 int /*<<< orphan*/  IOWAIT_PENDING_TID ; 
 int RVT_S_BUSY ; 
 int /*<<< orphan*/  iowait_set_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iowait_set_work_flag (struct iowait_work*) ; 

void hfi1_qp_unbusy(struct rvt_qp *qp, struct iowait_work *wait)
{
	struct hfi1_qp_priv *priv = qp->priv;

	if (iowait_set_work_flag(wait) == IOWAIT_IB_SE) {
		qp->s_flags &= ~RVT_S_BUSY;
		/*
		 * If we are sending a first-leg packet from the second leg,
		 * we need to clear the busy flag from priv->s_flags to
		 * avoid a race condition when the qp wakes up before
		 * the call to hfi1_verbs_send() returns to the second
		 * leg. In that case, the second leg will terminate without
		 * being re-scheduled, resulting in failure to send TID RDMA
		 * WRITE DATA and TID RDMA ACK packets.
		 */
		if (priv->s_flags & HFI1_S_TID_BUSY_SET) {
			priv->s_flags &= ~(HFI1_S_TID_BUSY_SET |
					   RVT_S_BUSY);
			iowait_set_flag(&priv->s_iowait, IOWAIT_PENDING_TID);
		}
	} else {
		priv->s_flags &= ~RVT_S_BUSY;
	}
}