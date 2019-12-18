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
struct rocker_desc_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ vlan_id; int /*<<< orphan*/  eth_dst; int /*<<< orphan*/  eth_src; int /*<<< orphan*/  group_id; } ;
struct ofdpa_group_tbl_entry {TYPE_1__ l2_rewrite; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_DST_MAC ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_GROUP_ID_LOWER ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_SRC_MAC ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_VLAN_ID ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_be16 (struct rocker_desc_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rocker_tlv_put_u32 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofdpa_cmd_group_tbl_add_l2_rewrite(struct rocker_desc_info *desc_info,
				   const struct ofdpa_group_tbl_entry *entry)
{
	if (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID_LOWER,
			       entry->l2_rewrite.group_id))
		return -EMSGSIZE;
	if (!is_zero_ether_addr(entry->l2_rewrite.eth_src) &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_SRC_MAC,
			   ETH_ALEN, entry->l2_rewrite.eth_src))
		return -EMSGSIZE;
	if (!is_zero_ether_addr(entry->l2_rewrite.eth_dst) &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC,
			   ETH_ALEN, entry->l2_rewrite.eth_dst))
		return -EMSGSIZE;
	if (entry->l2_rewrite.vlan_id &&
	    rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID,
				entry->l2_rewrite.vlan_id))
		return -EMSGSIZE;

	return 0;
}