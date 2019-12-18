#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfp_flower_tp_ports {int /*<<< orphan*/  port_dst; int /*<<< orphan*/  port_src; } ;
struct flow_rule {int dummy; } ;
struct flow_match_ports {TYPE_2__* mask; TYPE_1__* key; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_3__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_PORTS ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_rule_match_ports (struct flow_rule*,struct flow_match_ports*) ; 
 int /*<<< orphan*/  memset (struct nfp_flower_tp_ports*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nfp_flower_compile_tport(struct nfp_flower_tp_ports *ext,
			 struct nfp_flower_tp_ports *msk,
			 struct flow_cls_offload *flow)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(flow);

	memset(ext, 0, sizeof(struct nfp_flower_tp_ports));
	memset(msk, 0, sizeof(struct nfp_flower_tp_ports));

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) {
		struct flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		ext->port_src = match.key->src;
		ext->port_dst = match.key->dst;
		msk->port_src = match.mask->src;
		msk->port_dst = match.mask->dst;
	}
}