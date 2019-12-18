#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ib_qp_attr {int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  alt_port_num; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  port_num; } ;
struct ib_qp {TYPE_3__* qp_sec; } ;
struct TYPE_5__ {scalar_t__ state; TYPE_3__* sec; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  port_num; } ;
struct TYPE_4__ {scalar_t__ state; TYPE_3__* sec; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  port_num; } ;
struct ib_ports_pkeys {TYPE_2__ alt; TYPE_1__ main; } ;
struct TYPE_6__ {struct ib_ports_pkeys* ports_pkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_PORT_PKEY_NOT_VALID ; 
 void* IB_PORT_PKEY_VALID ; 
 int IB_QP_ALT_PATH ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 struct ib_ports_pkeys* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_ports_pkeys *get_new_pps(const struct ib_qp *qp,
					  const struct ib_qp_attr *qp_attr,
					  int qp_attr_mask)
{
	struct ib_ports_pkeys *new_pps;
	struct ib_ports_pkeys *qp_pps = qp->qp_sec->ports_pkeys;

	new_pps = kzalloc(sizeof(*new_pps), GFP_KERNEL);
	if (!new_pps)
		return NULL;

	if (qp_attr_mask & (IB_QP_PKEY_INDEX | IB_QP_PORT)) {
		if (!qp_pps) {
			new_pps->main.port_num = qp_attr->port_num;
			new_pps->main.pkey_index = qp_attr->pkey_index;
		} else {
			new_pps->main.port_num = (qp_attr_mask & IB_QP_PORT) ?
						  qp_attr->port_num :
						  qp_pps->main.port_num;

			new_pps->main.pkey_index =
					(qp_attr_mask & IB_QP_PKEY_INDEX) ?
					 qp_attr->pkey_index :
					 qp_pps->main.pkey_index;
		}
		new_pps->main.state = IB_PORT_PKEY_VALID;
	} else if (qp_pps) {
		new_pps->main.port_num = qp_pps->main.port_num;
		new_pps->main.pkey_index = qp_pps->main.pkey_index;
		if (qp_pps->main.state != IB_PORT_PKEY_NOT_VALID)
			new_pps->main.state = IB_PORT_PKEY_VALID;
	}

	if (qp_attr_mask & IB_QP_ALT_PATH) {
		new_pps->alt.port_num = qp_attr->alt_port_num;
		new_pps->alt.pkey_index = qp_attr->alt_pkey_index;
		new_pps->alt.state = IB_PORT_PKEY_VALID;
	} else if (qp_pps) {
		new_pps->alt.port_num = qp_pps->alt.port_num;
		new_pps->alt.pkey_index = qp_pps->alt.pkey_index;
		if (qp_pps->alt.state != IB_PORT_PKEY_NOT_VALID)
			new_pps->alt.state = IB_PORT_PKEY_VALID;
	}

	new_pps->main.sec = qp->qp_sec;
	new_pps->alt.sec = qp->qp_sec;
	return new_pps;
}