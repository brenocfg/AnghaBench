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
struct TYPE_5__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_6__ {TYPE_2__ ipv4; } ;
struct ip_tunnel_key {int /*<<< orphan*/  tp_dst; TYPE_3__ u; scalar_t__ tp_src; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct bnxt_tc_l2_key {int /*<<< orphan*/  inner_vlan_tci; int /*<<< orphan*/  inner_vlan_tpid; scalar_t__ num_vlans; int /*<<< orphan*/  smac; int /*<<< orphan*/  dmac; TYPE_1__ member_0; } ;
struct bnxt_tc_tunnel_node {scalar_t__ tunnel_handle; struct bnxt_tc_l2_key l2_info; } ;
struct bnxt_tc_info {int /*<<< orphan*/  decap_ht_params; int /*<<< orphan*/  decap_table; } ;
struct bnxt_tc_flow_node {struct bnxt_tc_tunnel_node* decap_node; } ;
struct bnxt_tc_flow {int /*<<< orphan*/  flags; struct ip_tunnel_key tun_key; } ;
struct bnxt {struct bnxt_tc_info* tc_info; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_TC_FLOW_FLAGS_TUNL_ETH_ADDRS ; 
 int ENOMEM ; 
 scalar_t__ INVALID_TUNNEL_HANDLE ; 
 int bnxt_tc_get_ref_decap_handle (struct bnxt*,struct bnxt_tc_flow*,struct bnxt_tc_l2_key*,struct bnxt_tc_flow_node*,scalar_t__*) ; 
 struct bnxt_tc_tunnel_node* bnxt_tc_get_tunnel_node (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ip_tunnel_key*) ; 
 int /*<<< orphan*/  bnxt_tc_put_decap_l2_node (struct bnxt*,struct bnxt_tc_flow_node*) ; 
 int /*<<< orphan*/  bnxt_tc_put_tunnel_node (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bnxt_tc_tunnel_node*) ; 
 int bnxt_tc_resolve_tunnel_hdrs (struct bnxt*,struct ip_tunnel_key*,struct bnxt_tc_l2_key*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hwrm_cfa_decap_filter_alloc (struct bnxt*,struct bnxt_tc_flow*,struct bnxt_tc_l2_key*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int bnxt_tc_get_decap_handle(struct bnxt *bp, struct bnxt_tc_flow *flow,
				    struct bnxt_tc_flow_node *flow_node,
				    __le32 *decap_filter_handle)
{
	struct ip_tunnel_key *decap_key = &flow->tun_key;
	struct bnxt_tc_info *tc_info = bp->tc_info;
	struct bnxt_tc_l2_key l2_info = { {0} };
	struct bnxt_tc_tunnel_node *decap_node;
	struct ip_tunnel_key tun_key = { 0 };
	struct bnxt_tc_l2_key *decap_l2_info;
	__le32 ref_decap_handle;
	int rc;

	/* Check if there's another flow using the same tunnel decap.
	 * If not, add this tunnel to the table and resolve the other
	 * tunnel header fileds. Ignore src_port in the tunnel_key,
	 * since it is not required for decap filters.
	 */
	decap_key->tp_src = 0;
	decap_node = bnxt_tc_get_tunnel_node(bp, &tc_info->decap_table,
					     &tc_info->decap_ht_params,
					     decap_key);
	if (!decap_node)
		return -ENOMEM;

	flow_node->decap_node = decap_node;

	if (decap_node->tunnel_handle != INVALID_TUNNEL_HANDLE)
		goto done;

	/* Resolve the L2 fields for tunnel decap
	 * Resolve the route for remote vtep (saddr) of the decap key
	 * Find it's next-hop mac addrs
	 */
	tun_key.u.ipv4.dst = flow->tun_key.u.ipv4.src;
	tun_key.tp_dst = flow->tun_key.tp_dst;
	rc = bnxt_tc_resolve_tunnel_hdrs(bp, &tun_key, &l2_info);
	if (rc)
		goto put_decap;

	decap_l2_info = &decap_node->l2_info;
	/* decap smac is wildcarded */
	ether_addr_copy(decap_l2_info->dmac, l2_info.smac);
	if (l2_info.num_vlans) {
		decap_l2_info->num_vlans = l2_info.num_vlans;
		decap_l2_info->inner_vlan_tpid = l2_info.inner_vlan_tpid;
		decap_l2_info->inner_vlan_tci = l2_info.inner_vlan_tci;
	}
	flow->flags |= BNXT_TC_FLOW_FLAGS_TUNL_ETH_ADDRS;

	/* For getting a decap_filter_handle we first need to check if
	 * there are any other decap flows that share the same tunnel L2
	 * key and if so, pass that flow's decap_filter_handle as the
	 * ref_decap_handle for this flow.
	 */
	rc = bnxt_tc_get_ref_decap_handle(bp, flow, decap_l2_info, flow_node,
					  &ref_decap_handle);
	if (rc)
		goto put_decap;

	/* Issue the hwrm cmd to allocate a decap filter handle */
	rc = hwrm_cfa_decap_filter_alloc(bp, flow, decap_l2_info,
					 ref_decap_handle,
					 &decap_node->tunnel_handle);
	if (rc)
		goto put_decap_l2;

done:
	*decap_filter_handle = decap_node->tunnel_handle;
	return 0;

put_decap_l2:
	bnxt_tc_put_decap_l2_node(bp, flow_node);
put_decap:
	bnxt_tc_put_tunnel_node(bp, &tc_info->decap_table,
				&tc_info->decap_ht_params,
				flow_node->decap_node);
	return rc;
}