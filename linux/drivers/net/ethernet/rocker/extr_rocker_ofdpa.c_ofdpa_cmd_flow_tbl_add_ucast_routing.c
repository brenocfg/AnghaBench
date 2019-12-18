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
struct rocker_desc_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  group_id; int /*<<< orphan*/  goto_tbl; int /*<<< orphan*/  dst4_mask; int /*<<< orphan*/  dst4; int /*<<< orphan*/  eth_type; } ;
struct TYPE_4__ {TYPE_1__ ucast_routing; } ;
struct ofdpa_flow_tbl_entry {TYPE_2__ key; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_DST_IP ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_DST_IP_MASK ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_ETHERTYPE ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_GOTO_TABLE_ID ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_GROUP_ID ; 
 scalar_t__ rocker_tlv_put_be16 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_be32 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u16 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u32 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofdpa_cmd_flow_tbl_add_ucast_routing(struct rocker_desc_info *desc_info,
				     const struct ofdpa_flow_tbl_entry *entry)
{
	if (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_ETHERTYPE,
				entry->key.ucast_routing.eth_type))
		return -EMSGSIZE;
	if (rocker_tlv_put_be32(desc_info, ROCKER_TLV_OF_DPA_DST_IP,
				entry->key.ucast_routing.dst4))
		return -EMSGSIZE;
	if (rocker_tlv_put_be32(desc_info, ROCKER_TLV_OF_DPA_DST_IP_MASK,
				entry->key.ucast_routing.dst4_mask))
		return -EMSGSIZE;
	if (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_GOTO_TABLE_ID,
			       entry->key.ucast_routing.goto_tbl))
		return -EMSGSIZE;
	if (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID,
			       entry->key.ucast_routing.group_id))
		return -EMSGSIZE;

	return 0;
}