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
struct rvt_qp {struct qib_qp_priv* priv; } ;
struct qib_qp_priv {int /*<<< orphan*/  s_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

void qib_stop_send_queue(struct rvt_qp *qp)
{
	struct qib_qp_priv *priv = qp->priv;

	cancel_work_sync(&priv->s_work);
}