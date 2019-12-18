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
typedef  int u32 ;
struct sdw_msg {int dev_num; int addr_page1; int addr_page2; scalar_t__ len; } ;
struct sdw_cdns {scalar_t__ msg_count; int* response_buf; int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_complete; } ;
typedef  enum sdw_command_response { ____Placeholder_sdw_command_response } sdw_command_response ;

/* Variables and functions */
 int CDNS_MCP_CMD_BASE ; 
 int /*<<< orphan*/  CDNS_MCP_CMD_COMMAND ; 
 int /*<<< orphan*/  CDNS_MCP_CMD_DEV_ADDR ; 
 int /*<<< orphan*/  CDNS_MCP_CMD_REG_ADDR_L ; 
 scalar_t__ CDNS_MCP_CMD_WORD_LEN ; 
 int CDNS_MCP_FIFOLEVEL ; 
 int CDNS_MCP_RESP_ACK ; 
 int CDNS_MCP_RESP_NACK ; 
 scalar_t__ CDNS_SCP_RX_FIFOLEVEL ; 
 int /*<<< orphan*/  CDNS_TX_TIMEOUT ; 
 int SDW_CMD_FAIL ; 
 int SDW_CMD_IGNORED ; 
 int SDW_CMD_OK ; 
 int SDW_CMD_TIMEOUT ; 
 int SDW_REG_SHIFT (int /*<<< orphan*/ ) ; 
 int SDW_SCP_ADDRPAGE1 ; 
 int SDW_SCP_ADDRPAGE2 ; 
 int /*<<< orphan*/  cdns_writel (struct sdw_cdns*,int,int) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum sdw_command_response
cdns_program_scp_addr(struct sdw_cdns *cdns, struct sdw_msg *msg)
{
	int nack = 0, no_ack = 0;
	unsigned long time;
	u32 data[2], base;
	int i;

	/* Program the watermark level for RX FIFO */
	if (cdns->msg_count != CDNS_SCP_RX_FIFOLEVEL) {
		cdns_writel(cdns, CDNS_MCP_FIFOLEVEL, CDNS_SCP_RX_FIFOLEVEL);
		cdns->msg_count = CDNS_SCP_RX_FIFOLEVEL;
	}

	data[0] = msg->dev_num << SDW_REG_SHIFT(CDNS_MCP_CMD_DEV_ADDR);
	data[0] |= 0x3 << SDW_REG_SHIFT(CDNS_MCP_CMD_COMMAND);
	data[1] = data[0];

	data[0] |= SDW_SCP_ADDRPAGE1 << SDW_REG_SHIFT(CDNS_MCP_CMD_REG_ADDR_L);
	data[1] |= SDW_SCP_ADDRPAGE2 << SDW_REG_SHIFT(CDNS_MCP_CMD_REG_ADDR_L);

	data[0] |= msg->addr_page1;
	data[1] |= msg->addr_page2;

	base = CDNS_MCP_CMD_BASE;
	cdns_writel(cdns, base, data[0]);
	base += CDNS_MCP_CMD_WORD_LEN;
	cdns_writel(cdns, base, data[1]);

	time = wait_for_completion_timeout(&cdns->tx_complete,
					   msecs_to_jiffies(CDNS_TX_TIMEOUT));
	if (!time) {
		dev_err(cdns->dev, "SCP Msg trf timed out\n");
		msg->len = 0;
		return SDW_CMD_TIMEOUT;
	}

	/* check response the writes */
	for (i = 0; i < 2; i++) {
		if (!(cdns->response_buf[i] & CDNS_MCP_RESP_ACK)) {
			no_ack = 1;
			dev_err(cdns->dev, "Program SCP Ack not received\n");
			if (cdns->response_buf[i] & CDNS_MCP_RESP_NACK) {
				nack = 1;
				dev_err(cdns->dev, "Program SCP NACK received\n");
			}
		}
	}

	/* For NACK, NO ack, don't return err if we are in Broadcast mode */
	if (nack) {
		dev_err_ratelimited(cdns->dev,
				    "SCP_addrpage NACKed for Slave %d\n", msg->dev_num);
		return SDW_CMD_FAIL;
	} else if (no_ack) {
		dev_dbg_ratelimited(cdns->dev,
				    "SCP_addrpage ignored for Slave %d\n", msg->dev_num);
		return SDW_CMD_IGNORED;
	}

	return SDW_CMD_OK;
}