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
struct qed_rdma_port {int /*<<< orphan*/  max_msg_size; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  port_state; } ;
struct qed_mcp_link_state {int /*<<< orphan*/  speed; scalar_t__ link_up; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; TYPE_1__* p_rdma_info; } ;
struct TYPE_6__ {TYPE_2__* mcp_info; } ;
struct TYPE_5__ {struct qed_mcp_link_state link_output; } ;
struct TYPE_4__ {struct qed_rdma_port* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* QED_LEADING_HWFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  QED_RDMA_PORT_DOWN ; 
 int /*<<< orphan*/  QED_RDMA_PORT_UP ; 
 int /*<<< orphan*/  RDMA_MAX_DATA_SIZE_IN_WQE ; 

__attribute__((used)) static struct qed_rdma_port *qed_rdma_query_port(void *rdma_cxt)
{
	struct qed_hwfn *p_hwfn = (struct qed_hwfn *)rdma_cxt;
	struct qed_rdma_port *p_port = p_hwfn->p_rdma_info->port;
	struct qed_mcp_link_state *p_link_output;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "RDMA Query port\n");

	/* The link state is saved only for the leading hwfn */
	p_link_output = &QED_LEADING_HWFN(p_hwfn->cdev)->mcp_info->link_output;

	p_port->port_state = p_link_output->link_up ? QED_RDMA_PORT_UP
	    : QED_RDMA_PORT_DOWN;

	p_port->link_speed = p_link_output->speed;

	p_port->max_msg_size = RDMA_MAX_DATA_SIZE_IN_WQE;

	return p_port;
}