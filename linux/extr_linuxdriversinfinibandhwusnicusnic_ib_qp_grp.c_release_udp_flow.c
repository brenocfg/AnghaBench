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
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;
struct usnic_ib_qp_grp_flow {TYPE_1__ udp; int /*<<< orphan*/  flow; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usnic_ib_qp_grp_flow*) ; 
 int /*<<< orphan*/  usnic_fwd_dealloc_flow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_transport_put_socket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_udp_flow(struct usnic_ib_qp_grp_flow *qp_flow)
{
	usnic_fwd_dealloc_flow(qp_flow->flow);
	usnic_transport_put_socket(qp_flow->udp.sock);
	kfree(qp_flow);
}