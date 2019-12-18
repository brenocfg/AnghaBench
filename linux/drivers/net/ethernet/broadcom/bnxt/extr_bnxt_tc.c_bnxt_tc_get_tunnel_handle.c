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
struct bnxt_tc_flow_node {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct bnxt_tc_flow {TYPE_1__ actions; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int BNXT_TC_ACTION_FLAG_TUNNEL_DECAP ; 
 int BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP ; 
 int bnxt_tc_get_decap_handle (struct bnxt*,struct bnxt_tc_flow*,struct bnxt_tc_flow_node*,int /*<<< orphan*/ *) ; 
 int bnxt_tc_get_encap_handle (struct bnxt*,struct bnxt_tc_flow*,struct bnxt_tc_flow_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_tc_get_tunnel_handle(struct bnxt *bp,
				     struct bnxt_tc_flow *flow,
				     struct bnxt_tc_flow_node *flow_node,
				     __le32 *tunnel_handle)
{
	if (flow->actions.flags & BNXT_TC_ACTION_FLAG_TUNNEL_DECAP)
		return bnxt_tc_get_decap_handle(bp, flow, flow_node,
						tunnel_handle);
	else if (flow->actions.flags & BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP)
		return bnxt_tc_get_encap_handle(bp, flow, flow_node,
						tunnel_handle);
	else
		return 0;
}