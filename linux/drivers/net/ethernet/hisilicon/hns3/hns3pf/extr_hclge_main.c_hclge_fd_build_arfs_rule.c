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
struct hclge_fd_rule_tuples {scalar_t__ ether_proto; scalar_t__ ip_proto; } ;
struct hclge_fd_rule {int unused_tuple; int /*<<< orphan*/  tuples_mask; int /*<<< orphan*/  tuples; int /*<<< orphan*/  flow_type; int /*<<< orphan*/  rule_type; scalar_t__ vf_id; scalar_t__ action; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ ETH_P_IP ; 
 int /*<<< orphan*/  HCLGE_FD_ARFS_ACTIVE ; 
 int /*<<< orphan*/  INNER_DST_MAC ; 
 int /*<<< orphan*/  INNER_IP_TOS ; 
 int /*<<< orphan*/  INNER_SRC_MAC ; 
 int /*<<< orphan*/  INNER_SRC_PORT ; 
 int /*<<< orphan*/  INNER_VLAN_TAG_FST ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  TCP_V4_FLOW ; 
 int /*<<< orphan*/  TCP_V6_FLOW ; 
 int /*<<< orphan*/  UDP_V4_FLOW ; 
 int /*<<< orphan*/  UDP_V6_FLOW ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct hclge_fd_rule_tuples const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void hclge_fd_build_arfs_rule(const struct hclge_fd_rule_tuples *tuples,
				     struct hclge_fd_rule *rule)
{
	rule->unused_tuple = BIT(INNER_SRC_MAC) | BIT(INNER_DST_MAC) |
			     BIT(INNER_VLAN_TAG_FST) | BIT(INNER_IP_TOS) |
			     BIT(INNER_SRC_PORT);
	rule->action = 0;
	rule->vf_id = 0;
	rule->rule_type = HCLGE_FD_ARFS_ACTIVE;
	if (tuples->ether_proto == ETH_P_IP) {
		if (tuples->ip_proto == IPPROTO_TCP)
			rule->flow_type = TCP_V4_FLOW;
		else
			rule->flow_type = UDP_V4_FLOW;
	} else {
		if (tuples->ip_proto == IPPROTO_TCP)
			rule->flow_type = TCP_V6_FLOW;
		else
			rule->flow_type = UDP_V6_FLOW;
	}
	memcpy(&rule->tuples, tuples, sizeof(rule->tuples));
	memset(&rule->tuples_mask, 0xFF, sizeof(rule->tuples_mask));
}