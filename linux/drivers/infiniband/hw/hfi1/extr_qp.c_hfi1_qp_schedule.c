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
struct rvt_qp {struct hfi1_qp_priv* priv; } ;
struct hfi1_qp_priv {int /*<<< orphan*/  s_iowait; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOWAIT_PENDING_IB ; 
 int /*<<< orphan*/  IOWAIT_PENDING_TID ; 
 int hfi1_schedule_send (struct rvt_qp*) ; 
 int hfi1_schedule_tid_send (struct rvt_qp*) ; 
 int /*<<< orphan*/  iowait_clear_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iowait_flag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfi1_qp_schedule(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;
	bool ret;

	if (iowait_flag_set(&priv->s_iowait, IOWAIT_PENDING_IB)) {
		ret = hfi1_schedule_send(qp);
		if (ret)
			iowait_clear_flag(&priv->s_iowait, IOWAIT_PENDING_IB);
	}
	if (iowait_flag_set(&priv->s_iowait, IOWAIT_PENDING_TID)) {
		ret = hfi1_schedule_tid_send(qp);
		if (ret)
			iowait_clear_flag(&priv->s_iowait, IOWAIT_PENDING_TID);
	}
}