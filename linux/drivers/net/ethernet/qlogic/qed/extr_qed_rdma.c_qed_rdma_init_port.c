#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qed_rdma_port {scalar_t__ pkey_bad_counter; int /*<<< orphan*/  max_msg_size; int /*<<< orphan*/  port_state; } ;
struct qed_rdma_device {int max_mr_mw_fmr_size; } ;
struct qed_hwfn {TYPE_1__* cdev; TYPE_3__* mcp_info; TYPE_2__* p_rdma_info; } ;
struct TYPE_8__ {scalar_t__ link_up; } ;
struct TYPE_7__ {TYPE_4__ link_output; } ;
struct TYPE_6__ {struct qed_rdma_device* dev; struct qed_rdma_port* port; } ;
struct TYPE_5__ {int rdma_max_sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  QED_RDMA_PORT_DOWN ; 
 int /*<<< orphan*/  QED_RDMA_PORT_UP ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static void qed_rdma_init_port(struct qed_hwfn *p_hwfn)
{
	struct qed_rdma_port *port = p_hwfn->p_rdma_info->port;
	struct qed_rdma_device *dev = p_hwfn->p_rdma_info->dev;

	port->port_state = p_hwfn->mcp_info->link_output.link_up ?
			   QED_RDMA_PORT_UP : QED_RDMA_PORT_DOWN;

	port->max_msg_size = min_t(u64,
				   (dev->max_mr_mw_fmr_size *
				    p_hwfn->cdev->rdma_max_sge),
				   BIT(31));

	port->pkey_bad_counter = 0;
}