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
typedef  void* u8 ;
typedef  int u16 ;
struct nfp_flower_meta_tci {void* tci; int /*<<< orphan*/  mask_id; void* nfp_flow_key_layer; } ;
struct flow_rule {int dummy; } ;
struct flow_match_vlan {TYPE_2__* mask; TYPE_1__* key; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  vlan_priority; } ;
struct TYPE_3__ {int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  vlan_priority; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_VLAN ; 
 int NFP_FLOWER_MASK_VLAN_PRESENT ; 
 int /*<<< orphan*/  NFP_FLOWER_MASK_VLAN_PRIO ; 
 int /*<<< orphan*/  NFP_FLOWER_MASK_VLAN_VID ; 
 void* cpu_to_be16 (int) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_rule_match_vlan (struct flow_rule*,struct flow_match_vlan*) ; 
 int /*<<< orphan*/  memset (struct nfp_flower_meta_tci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nfp_flower_compile_meta_tci(struct nfp_flower_meta_tci *ext,
			    struct nfp_flower_meta_tci *msk,
			    struct flow_cls_offload *flow, u8 key_type)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(flow);
	u16 tmp_tci;

	memset(ext, 0, sizeof(struct nfp_flower_meta_tci));
	memset(msk, 0, sizeof(struct nfp_flower_meta_tci));

	/* Populate the metadata frame. */
	ext->nfp_flow_key_layer = key_type;
	ext->mask_id = ~0;

	msk->nfp_flow_key_layer = key_type;
	msk->mask_id = ~0;

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) {
		struct flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		/* Populate the tci field. */
		tmp_tci = NFP_FLOWER_MASK_VLAN_PRESENT;
		tmp_tci |= FIELD_PREP(NFP_FLOWER_MASK_VLAN_PRIO,
				      match.key->vlan_priority) |
			   FIELD_PREP(NFP_FLOWER_MASK_VLAN_VID,
				      match.key->vlan_id);
		ext->tci = cpu_to_be16(tmp_tci);

		tmp_tci = NFP_FLOWER_MASK_VLAN_PRESENT;
		tmp_tci |= FIELD_PREP(NFP_FLOWER_MASK_VLAN_PRIO,
				      match.mask->vlan_priority) |
			   FIELD_PREP(NFP_FLOWER_MASK_VLAN_VID,
				      match.mask->vlan_id);
		msk->tci = cpu_to_be16(tmp_tci);
	}
}