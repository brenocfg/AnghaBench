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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {struct qib_qp_priv* priv; int /*<<< orphan*/  port_num; TYPE_1__ ibqp; } ;
struct qib_qp_priv {int /*<<< orphan*/  s_work; } ;
struct qib_pportdata {int /*<<< orphan*/  qib_wq; } ;
struct qib_ibport {int dummy; } ;

/* Variables and functions */
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qib_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool _qib_schedule_send(struct rvt_qp *qp)
{
	struct qib_ibport *ibp =
		to_iport(qp->ibqp.device, qp->port_num);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	struct qib_qp_priv *priv = qp->priv;

	return queue_work(ppd->qib_wq, &priv->s_work);
}