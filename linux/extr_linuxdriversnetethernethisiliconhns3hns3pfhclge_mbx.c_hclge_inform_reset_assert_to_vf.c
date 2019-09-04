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
typedef  scalar_t__ u8 ;
struct hclge_vport {int /*<<< orphan*/  vport_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MBX_ASSERTING_RESET ; 
 int hclge_send_mbx_msg (struct hclge_vport*,scalar_t__*,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hclge_inform_reset_assert_to_vf(struct hclge_vport *vport)
{
	u8 msg_data[2];
	u8 dest_vfid;

	dest_vfid = (u8)vport->vport_id;

	/* send this requested info to VF */
	return hclge_send_mbx_msg(vport, msg_data, sizeof(u8),
				  HCLGE_MBX_ASSERTING_RESET, dest_vfid);
}