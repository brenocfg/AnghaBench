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
typedef  int /*<<< orphan*/  u16 ;
struct hclge_vport {int dummy; } ;
typedef  int /*<<< orphan*/  msg_data ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MBX_PUSH_VLAN_INFO ; 
 int MSG_DATA_SIZE ; 
 int hclge_send_mbx_msg (struct hclge_vport*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int hclge_push_vf_port_base_vlan_info(struct hclge_vport *vport, u8 vfid,
				      u16 state, u16 vlan_tag, u16 qos,
				      u16 vlan_proto)
{
#define MSG_DATA_SIZE	8

	u8 msg_data[MSG_DATA_SIZE];

	memcpy(&msg_data[0], &state, sizeof(u16));
	memcpy(&msg_data[2], &vlan_proto, sizeof(u16));
	memcpy(&msg_data[4], &qos, sizeof(u16));
	memcpy(&msg_data[6], &vlan_tag, sizeof(u16));

	return hclge_send_mbx_msg(vport, msg_data, sizeof(msg_data),
				  HCLGE_MBX_PUSH_VLAN_INFO, vfid);
}