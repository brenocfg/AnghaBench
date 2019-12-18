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
struct rocker_tlv {int dummy; } ;
struct rocker_port {int dummy; } ;
struct rocker_desc_info {int dummy; } ;
struct ofdpa_group_tbl_entry {int /*<<< orphan*/  group_id; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOTSUPP ; 
 int ROCKER_GROUP_TYPE_GET (int /*<<< orphan*/ ) ; 
#define  ROCKER_OF_DPA_GROUP_TYPE_L2_FLOOD 132 
#define  ROCKER_OF_DPA_GROUP_TYPE_L2_INTERFACE 131 
#define  ROCKER_OF_DPA_GROUP_TYPE_L2_MCAST 130 
#define  ROCKER_OF_DPA_GROUP_TYPE_L2_REWRITE 129 
#define  ROCKER_OF_DPA_GROUP_TYPE_L3_UCAST 128 
 int /*<<< orphan*/  ROCKER_TLV_CMD_INFO ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_TYPE ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_GROUP_ID ; 
 int ofdpa_cmd_group_tbl_add_group_ids (struct rocker_desc_info*,struct ofdpa_group_tbl_entry*) ; 
 int ofdpa_cmd_group_tbl_add_l2_interface (struct rocker_desc_info*,struct ofdpa_group_tbl_entry*) ; 
 int ofdpa_cmd_group_tbl_add_l2_rewrite (struct rocker_desc_info*,struct ofdpa_group_tbl_entry*) ; 
 int ofdpa_cmd_group_tbl_add_l3_unicast (struct rocker_desc_info*,struct ofdpa_group_tbl_entry*) ; 
 int /*<<< orphan*/  rocker_tlv_nest_end (struct rocker_desc_info*,struct rocker_tlv*) ; 
 struct rocker_tlv* rocker_tlv_nest_start (struct rocker_desc_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u16 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u32 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_cmd_group_tbl_add(const struct rocker_port *rocker_port,
				   struct rocker_desc_info *desc_info,
				   void *priv)
{
	struct ofdpa_group_tbl_entry *entry = priv;
	struct rocker_tlv *cmd_info;
	int err = 0;

	if (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE, entry->cmd))
		return -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	if (!cmd_info)
		return -EMSGSIZE;

	if (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID,
			       entry->group_id))
		return -EMSGSIZE;

	switch (ROCKER_GROUP_TYPE_GET(entry->group_id)) {
	case ROCKER_OF_DPA_GROUP_TYPE_L2_INTERFACE:
		err = ofdpa_cmd_group_tbl_add_l2_interface(desc_info, entry);
		break;
	case ROCKER_OF_DPA_GROUP_TYPE_L2_REWRITE:
		err = ofdpa_cmd_group_tbl_add_l2_rewrite(desc_info, entry);
		break;
	case ROCKER_OF_DPA_GROUP_TYPE_L2_FLOOD:
	case ROCKER_OF_DPA_GROUP_TYPE_L2_MCAST:
		err = ofdpa_cmd_group_tbl_add_group_ids(desc_info, entry);
		break;
	case ROCKER_OF_DPA_GROUP_TYPE_L3_UCAST:
		err = ofdpa_cmd_group_tbl_add_l3_unicast(desc_info, entry);
		break;
	default:
		err = -ENOTSUPP;
		break;
	}

	if (err)
		return err;

	rocker_tlv_nest_end(desc_info, cmd_info);

	return 0;
}