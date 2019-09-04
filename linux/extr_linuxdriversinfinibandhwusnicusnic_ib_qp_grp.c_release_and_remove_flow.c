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
struct usnic_ib_qp_grp_flow {int trans_type; int /*<<< orphan*/  link; } ;

/* Variables and functions */
#define  USNIC_TRANSPORT_IPV4_UDP 129 
#define  USNIC_TRANSPORT_ROCE_CUSTOM 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_roce_custom_flow (struct usnic_ib_qp_grp_flow*) ; 
 int /*<<< orphan*/  release_udp_flow (struct usnic_ib_qp_grp_flow*) ; 
 int /*<<< orphan*/  usnic_debugfs_flow_remove (struct usnic_ib_qp_grp_flow*) ; 

__attribute__((used)) static void release_and_remove_flow(struct usnic_ib_qp_grp_flow *qp_flow)
{
	usnic_debugfs_flow_remove(qp_flow);
	list_del(&qp_flow->link);

	switch (qp_flow->trans_type) {
	case USNIC_TRANSPORT_ROCE_CUSTOM:
		release_roce_custom_flow(qp_flow);
		break;
	case USNIC_TRANSPORT_IPV4_UDP:
		release_udp_flow(qp_flow);
		break;
	default:
		WARN(1, "Unsupported transport %u\n",
				qp_flow->trans_type);
		break;
	}
}