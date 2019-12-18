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
struct sdw_msg {int* buf; int /*<<< orphan*/  dev_num; } ;
struct sdw_cdns {int* response_buf; int /*<<< orphan*/  dev; } ;
typedef  enum sdw_command_response { ____Placeholder_sdw_command_response } sdw_command_response ;

/* Variables and functions */
 int CDNS_MCP_RESP_ACK ; 
 int CDNS_MCP_RESP_NACK ; 
 int /*<<< orphan*/  CDNS_MCP_RESP_RDATA ; 
 int SDW_CMD_FAIL ; 
 int SDW_CMD_IGNORED ; 
 int SDW_CMD_OK ; 
 int SDW_REG_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static enum sdw_command_response
cdns_fill_msg_resp(struct sdw_cdns *cdns,
		   struct sdw_msg *msg, int count, int offset)
{
	int nack = 0, no_ack = 0;
	int i;

	/* check message response */
	for (i = 0; i < count; i++) {
		if (!(cdns->response_buf[i] & CDNS_MCP_RESP_ACK)) {
			no_ack = 1;
			dev_dbg_ratelimited(cdns->dev, "Msg Ack not received\n");
			if (cdns->response_buf[i] & CDNS_MCP_RESP_NACK) {
				nack = 1;
				dev_err_ratelimited(cdns->dev, "Msg NACK received\n");
			}
		}
	}

	if (nack) {
		dev_err_ratelimited(cdns->dev, "Msg NACKed for Slave %d\n", msg->dev_num);
		return SDW_CMD_FAIL;
	} else if (no_ack) {
		dev_dbg_ratelimited(cdns->dev, "Msg ignored for Slave %d\n", msg->dev_num);
		return SDW_CMD_IGNORED;
	}

	/* fill response */
	for (i = 0; i < count; i++)
		msg->buf[i + offset] = cdns->response_buf[i] >>
				SDW_REG_SHIFT(CDNS_MCP_RESP_RDATA);

	return SDW_CMD_OK;
}