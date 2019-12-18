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
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {TYPE_2__ ibqp; int /*<<< orphan*/  port_num; struct hfi1_qp_priv* priv; } ;
struct hfi1_qp_priv {TYPE_1__* s_sde; int /*<<< orphan*/  s_iowait; } ;
struct hfi1_pportdata {int /*<<< orphan*/  hfi1_wq; } ;
struct hfi1_ibport {int dummy; } ;
struct hfi1_devdata {int /*<<< orphan*/  node; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_node (int /*<<< orphan*/ ) ; 
 struct hfi1_devdata* dd_from_ibdev (int /*<<< orphan*/ ) ; 
 int iowait_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 struct hfi1_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool _hfi1_schedule_send(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;
	struct hfi1_ibport *ibp =
		to_iport(qp->ibqp.device, qp->port_num);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	struct hfi1_devdata *dd = dd_from_ibdev(qp->ibqp.device);

	return iowait_schedule(&priv->s_iowait, ppd->hfi1_wq,
			       priv->s_sde ?
			       priv->s_sde->cpu :
			       cpumask_first(cpumask_of_node(dd->node)));
}