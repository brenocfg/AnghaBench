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
struct bnxt_tc_flow_node {int /*<<< orphan*/  encap_node; } ;
struct TYPE_2__ {int flags; } ;
struct bnxt_tc_flow {TYPE_1__ actions; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int BNXT_TC_ACTION_FLAG_TUNNEL_DECAP ; 
 int BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP ; 
 int /*<<< orphan*/  bnxt_tc_put_decap_handle (struct bnxt*,struct bnxt_tc_flow_node*) ; 
 int /*<<< orphan*/  bnxt_tc_put_encap_handle (struct bnxt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_tc_put_tunnel_handle(struct bnxt *bp,
				      struct bnxt_tc_flow *flow,
				      struct bnxt_tc_flow_node *flow_node)
{
	if (flow->actions.flags & BNXT_TC_ACTION_FLAG_TUNNEL_DECAP)
		bnxt_tc_put_decap_handle(bp, flow_node);
	else if (flow->actions.flags & BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP)
		bnxt_tc_put_encap_handle(bp, flow_node->encap_node);
}