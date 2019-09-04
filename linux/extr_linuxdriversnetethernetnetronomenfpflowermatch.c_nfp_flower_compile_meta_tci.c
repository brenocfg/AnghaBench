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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct tc_cls_flower_offload {int /*<<< orphan*/  dissector; struct fl_flow_key* key; struct fl_flow_key* mask; } ;
struct nfp_flower_meta_tci {int /*<<< orphan*/  tci; int /*<<< orphan*/  mask_id; int /*<<< orphan*/  nfp_flow_key_layer; } ;
struct flow_dissector_key_vlan {int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  vlan_priority; } ;
struct fl_flow_key {int dummy; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_VLAN ; 
 int NFP_FLOWER_MASK_VLAN_PRESENT ; 
 int /*<<< orphan*/  NFP_FLOWER_MASK_VLAN_PRIO ; 
 int /*<<< orphan*/  NFP_FLOWER_MASK_VLAN_VID ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfp_flower_meta_tci*,int /*<<< orphan*/ ,int) ; 
 struct flow_dissector_key_vlan* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fl_flow_key*) ; 

__attribute__((used)) static void
nfp_flower_compile_meta_tci(struct nfp_flower_meta_tci *frame,
			    struct tc_cls_flower_offload *flow, u8 key_type,
			    bool mask_version)
{
	struct fl_flow_key *target = mask_version ? flow->mask : flow->key;
	struct flow_dissector_key_vlan *flow_vlan;
	u16 tmp_tci;

	memset(frame, 0, sizeof(struct nfp_flower_meta_tci));
	/* Populate the metadata frame. */
	frame->nfp_flow_key_layer = key_type;
	frame->mask_id = ~0;

	if (dissector_uses_key(flow->dissector, FLOW_DISSECTOR_KEY_VLAN)) {
		flow_vlan = skb_flow_dissector_target(flow->dissector,
						      FLOW_DISSECTOR_KEY_VLAN,
						      target);
		/* Populate the tci field. */
		tmp_tci = NFP_FLOWER_MASK_VLAN_PRESENT;
		tmp_tci |= FIELD_PREP(NFP_FLOWER_MASK_VLAN_PRIO,
				      flow_vlan->vlan_priority) |
			   FIELD_PREP(NFP_FLOWER_MASK_VLAN_VID,
				      flow_vlan->vlan_id);
		frame->tci = cpu_to_be16(tmp_tci);
	}
}