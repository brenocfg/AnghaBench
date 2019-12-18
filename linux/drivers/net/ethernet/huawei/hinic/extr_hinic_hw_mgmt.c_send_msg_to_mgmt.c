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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct hinic_pf_to_mgmt {int /*<<< orphan*/  sync_msg_buf; struct hinic_api_cmd_chain** cmd_chain; } ;
struct hinic_api_cmd_chain {int dummy; } ;
typedef  enum msg_ack_type { ____Placeholder_msg_ack_type } msg_ack_type ;
typedef  enum mgmt_direction_type { ____Placeholder_mgmt_direction_type } mgmt_direction_type ;
typedef  enum hinic_mod_type { ____Placeholder_hinic_mod_type } hinic_mod_type ;

/* Variables and functions */
 size_t HINIC_API_CMD_WRITE_TO_MGMT_CPU ; 
 int /*<<< orphan*/  HINIC_NODE_ID_MGMT ; 
 int MGMT_RESP ; 
 int /*<<< orphan*/  SYNC_MSG_ID (struct hinic_pf_to_mgmt*) ; 
 int /*<<< orphan*/  SYNC_MSG_ID_INC (struct hinic_pf_to_mgmt*) ; 
 int hinic_api_cmd_write (struct hinic_api_cmd_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_msg_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_header (struct hinic_pf_to_mgmt*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_mgmt_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_msg_to_mgmt(struct hinic_pf_to_mgmt *pf_to_mgmt,
			    enum hinic_mod_type mod, u8 cmd,
			    u8 *data, u16 data_len,
			    enum msg_ack_type ack_type,
			    enum mgmt_direction_type direction,
			    u16 resp_msg_id)
{
	struct hinic_api_cmd_chain *chain;
	u64 header;
	u16 msg_id;

	msg_id = SYNC_MSG_ID(pf_to_mgmt);

	if (direction == MGMT_RESP) {
		header = prepare_header(pf_to_mgmt, data_len, mod, ack_type,
					direction, cmd, resp_msg_id);
	} else {
		SYNC_MSG_ID_INC(pf_to_mgmt);
		header = prepare_header(pf_to_mgmt, data_len, mod, ack_type,
					direction, cmd, msg_id);
	}

	prepare_mgmt_cmd(pf_to_mgmt->sync_msg_buf, &header, data, data_len);

	chain = pf_to_mgmt->cmd_chain[HINIC_API_CMD_WRITE_TO_MGMT_CPU];
	return hinic_api_cmd_write(chain, HINIC_NODE_ID_MGMT,
				   pf_to_mgmt->sync_msg_buf,
				   mgmt_msg_len(data_len));
}