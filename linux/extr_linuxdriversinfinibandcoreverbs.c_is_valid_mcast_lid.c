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
typedef  scalar_t__ u16 ;
struct ib_qp_init_attr {int dummy; } ;
struct ib_qp_attr {scalar_t__ qp_state; int port_num; } ;
struct ib_qp {TYPE_1__* device; } ;
struct TYPE_2__ {int phys_port_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 int /*<<< orphan*/  IB_MULTICAST_LID_BASE ; 
 scalar_t__ IB_QPS_INIT ; 
 int IB_QP_PORT ; 
 int IB_QP_STATE ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_query_qp (struct ib_qp*,struct ib_qp_attr*,int,struct ib_qp_init_attr*) ; 
 scalar_t__ rdma_port_get_link_layer (TYPE_1__*,int) ; 

__attribute__((used)) static bool is_valid_mcast_lid(struct ib_qp *qp, u16 lid)
{
	struct ib_qp_init_attr init_attr = {};
	struct ib_qp_attr attr = {};
	int num_eth_ports = 0;
	int port;

	/* If QP state >= init, it is assigned to a port and we can check this
	 * port only.
	 */
	if (!ib_query_qp(qp, &attr, IB_QP_STATE | IB_QP_PORT, &init_attr)) {
		if (attr.qp_state >= IB_QPS_INIT) {
			if (rdma_port_get_link_layer(qp->device, attr.port_num) !=
			    IB_LINK_LAYER_INFINIBAND)
				return true;
			goto lid_check;
		}
	}

	/* Can't get a quick answer, iterate over all ports */
	for (port = 0; port < qp->device->phys_port_cnt; port++)
		if (rdma_port_get_link_layer(qp->device, port) !=
		    IB_LINK_LAYER_INFINIBAND)
			num_eth_ports++;

	/* If we have at lease one Ethernet port, RoCE annex declares that
	 * multicast LID should be ignored. We can't tell at this step if the
	 * QP belongs to an IB or Ethernet port.
	 */
	if (num_eth_ports)
		return true;

	/* If all the ports are IB, we can check according to IB spec. */
lid_check:
	return !(lid < be16_to_cpu(IB_MULTICAST_LID_BASE) ||
		 lid == be16_to_cpu(IB_LID_PERMISSIVE));
}