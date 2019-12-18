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
typedef  int u8 ;
struct nfp_flower_tp_ports {int dummy; } ;
struct nfp_flower_meta_tci {int nfp_flow_key_layer; int /*<<< orphan*/  tci; } ;
struct nfp_flower_merge_check {int /*<<< orphan*/  ipv6; int /*<<< orphan*/  ipv4; int /*<<< orphan*/  l4; int /*<<< orphan*/  l2; int /*<<< orphan*/  tci; } ;
struct nfp_flower_mac_mpls {int dummy; } ;
struct nfp_flower_ipv6 {int dummy; } ;
struct nfp_flower_ipv4 {int dummy; } ;
struct nfp_flower_in_port {int dummy; } ;
struct nfp_flower_ext_meta {int dummy; } ;
struct nfp_fl_payload {int* mask_data; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int NFP_FLOWER_LAYER_EXT_META ; 
 int NFP_FLOWER_LAYER_IPV4 ; 
 int NFP_FLOWER_LAYER_IPV6 ; 
 int NFP_FLOWER_LAYER_MAC ; 
 int NFP_FLOWER_LAYER_TP ; 
 int NFP_FLOWER_MERGE_FIELDS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (struct nfp_flower_merge_check*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nfp_flower_populate_merge_match(struct nfp_fl_payload *flow,
				struct nfp_flower_merge_check *merge,
				bool extra_fields)
{
	struct nfp_flower_meta_tci *meta_tci;
	u8 *mask = flow->mask_data;
	u8 key_layer, match_size;

	memset(merge, 0, sizeof(struct nfp_flower_merge_check));

	meta_tci = (struct nfp_flower_meta_tci *)mask;
	key_layer = meta_tci->nfp_flow_key_layer;

	if (key_layer & ~NFP_FLOWER_MERGE_FIELDS && !extra_fields)
		return -EOPNOTSUPP;

	merge->tci = meta_tci->tci;
	mask += sizeof(struct nfp_flower_meta_tci);

	if (key_layer & NFP_FLOWER_LAYER_EXT_META)
		mask += sizeof(struct nfp_flower_ext_meta);

	mask += sizeof(struct nfp_flower_in_port);

	if (key_layer & NFP_FLOWER_LAYER_MAC) {
		match_size = sizeof(struct nfp_flower_mac_mpls);
		memcpy(&merge->l2, mask, match_size);
		mask += match_size;
	}

	if (key_layer & NFP_FLOWER_LAYER_TP) {
		match_size = sizeof(struct nfp_flower_tp_ports);
		memcpy(&merge->l4, mask, match_size);
		mask += match_size;
	}

	if (key_layer & NFP_FLOWER_LAYER_IPV4) {
		match_size = sizeof(struct nfp_flower_ipv4);
		memcpy(&merge->ipv4, mask, match_size);
	}

	if (key_layer & NFP_FLOWER_LAYER_IPV6) {
		match_size = sizeof(struct nfp_flower_ipv6);
		memcpy(&merge->ipv6, mask, match_size);
	}

	return 0;
}