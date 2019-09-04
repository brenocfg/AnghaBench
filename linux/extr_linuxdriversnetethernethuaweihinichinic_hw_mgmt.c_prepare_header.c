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
typedef  int u64 ;
typedef  int u16 ;
struct hinic_pf_to_mgmt {struct hinic_hwif* hwif; } ;
struct hinic_hwif {int dummy; } ;
typedef  enum msg_ack_type { ____Placeholder_msg_ack_type } msg_ack_type ;
typedef  enum mgmt_direction_type { ____Placeholder_mgmt_direction_type } mgmt_direction_type ;
typedef  enum hinic_mod_type { ____Placeholder_hinic_mod_type } hinic_mod_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_MGMT_TO_PF ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  DIRECTION ; 
 int HINIC_HWIF_PCI_INTF (struct hinic_hwif*) ; 
 int HINIC_HWIF_PF_IDX (struct hinic_hwif*) ; 
 int HINIC_MSG_HEADER_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAST ; 
 int LAST_SEGMENT ; 
 int /*<<< orphan*/  MODULE ; 
 int /*<<< orphan*/  MSG_ID ; 
 int /*<<< orphan*/  MSG_LEN ; 
 int /*<<< orphan*/  NO_ACK ; 
 int /*<<< orphan*/  PCI_INTF ; 
 int /*<<< orphan*/  PF_IDX ; 
 int SEGMENT_LEN ; 
 int /*<<< orphan*/  SEG_LEN ; 
 int /*<<< orphan*/  SEQID ; 

__attribute__((used)) static u64 prepare_header(struct hinic_pf_to_mgmt *pf_to_mgmt,
			  u16 msg_len, enum hinic_mod_type mod,
			  enum msg_ack_type ack_type,
			  enum mgmt_direction_type direction,
			  u16 cmd, u16 msg_id)
{
	struct hinic_hwif *hwif = pf_to_mgmt->hwif;

	return HINIC_MSG_HEADER_SET(msg_len, MSG_LEN)           |
	       HINIC_MSG_HEADER_SET(mod, MODULE)                |
	       HINIC_MSG_HEADER_SET(SEGMENT_LEN, SEG_LEN)       |
	       HINIC_MSG_HEADER_SET(ack_type, NO_ACK)           |
	       HINIC_MSG_HEADER_SET(0, ASYNC_MGMT_TO_PF)        |
	       HINIC_MSG_HEADER_SET(0, SEQID)                   |
	       HINIC_MSG_HEADER_SET(LAST_SEGMENT, LAST)         |
	       HINIC_MSG_HEADER_SET(direction, DIRECTION)       |
	       HINIC_MSG_HEADER_SET(cmd, CMD)                   |
	       HINIC_MSG_HEADER_SET(HINIC_HWIF_PCI_INTF(hwif), PCI_INTF) |
	       HINIC_MSG_HEADER_SET(HINIC_HWIF_PF_IDX(hwif), PF_IDX)     |
	       HINIC_MSG_HEADER_SET(msg_id, MSG_ID);
}