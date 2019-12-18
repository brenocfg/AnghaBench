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
struct rvt_qp {struct hfi1_qp_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  trigger_work; } ;
struct hfi1_qp_priv {TYPE_1__ tid_rdma; int /*<<< orphan*/  s_iowait; } ;

/* Variables and functions */
 scalar_t__ cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowait_cancel_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_put_qp (struct rvt_qp*) ; 

void stop_send_queue(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;

	iowait_cancel_work(&priv->s_iowait);
	if (cancel_work_sync(&priv->tid_rdma.trigger_work))
		rvt_put_qp(qp);
}