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
struct ip_tunnel_key {int dummy; } ;
struct bnxt_tc_tunnel_node {scalar_t__ tunnel_handle; int /*<<< orphan*/  l2_info; } ;
struct bnxt_tc_info {int /*<<< orphan*/  encap_ht_params; int /*<<< orphan*/  encap_table; } ;
struct bnxt_tc_flow_node {struct bnxt_tc_tunnel_node* encap_node; } ;
struct TYPE_2__ {struct ip_tunnel_key tun_encap_key; } ;
struct bnxt_tc_flow {TYPE_1__ actions; } ;
struct bnxt {struct bnxt_tc_info* tc_info; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ INVALID_TUNNEL_HANDLE ; 
 struct bnxt_tc_tunnel_node* bnxt_tc_get_tunnel_node (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ip_tunnel_key*) ; 
 int /*<<< orphan*/  bnxt_tc_put_tunnel_node (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bnxt_tc_tunnel_node*) ; 
 int bnxt_tc_resolve_tunnel_hdrs (struct bnxt*,struct ip_tunnel_key*,int /*<<< orphan*/ *) ; 
 int hwrm_cfa_encap_record_alloc (struct bnxt*,struct ip_tunnel_key*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static int bnxt_tc_get_encap_handle(struct bnxt *bp, struct bnxt_tc_flow *flow,
				    struct bnxt_tc_flow_node *flow_node,
				    __le32 *encap_handle)
{
	struct ip_tunnel_key *encap_key = &flow->actions.tun_encap_key;
	struct bnxt_tc_info *tc_info = bp->tc_info;
	struct bnxt_tc_tunnel_node *encap_node;
	int rc;

	/* Check if there's another flow using the same tunnel encap.
	 * If not, add this tunnel to the table and resolve the other
	 * tunnel header fileds
	 */
	encap_node = bnxt_tc_get_tunnel_node(bp, &tc_info->encap_table,
					     &tc_info->encap_ht_params,
					     encap_key);
	if (!encap_node)
		return -ENOMEM;

	flow_node->encap_node = encap_node;

	if (encap_node->tunnel_handle != INVALID_TUNNEL_HANDLE)
		goto done;

	rc = bnxt_tc_resolve_tunnel_hdrs(bp, encap_key, &encap_node->l2_info);
	if (rc)
		goto put_encap;

	/* Allocate a new tunnel encap record */
	rc = hwrm_cfa_encap_record_alloc(bp, encap_key, &encap_node->l2_info,
					 &encap_node->tunnel_handle);
	if (rc)
		goto put_encap;

done:
	*encap_handle = encap_node->tunnel_handle;
	return 0;

put_encap:
	bnxt_tc_put_tunnel_node(bp, &tc_info->encap_table,
				&tc_info->encap_ht_params, encap_node);
	return rc;
}