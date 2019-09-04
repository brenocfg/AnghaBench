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
struct sun6i_dsi {int /*<<< orphan*/  regs; } ;
struct mipi_dsi_msg {int tx_len; int /*<<< orphan*/ * tx_buf; } ;
typedef  int /*<<< orphan*/  crc ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_START_LPTX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SUN6I_DSI_CMD_CTL_REG ; 
 int /*<<< orphan*/  SUN6I_DSI_CMD_TX_REG (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun6i_dsi_crc_compute (int /*<<< orphan*/ *,int) ; 
 int sun6i_dsi_dcs_build_pkt_hdr (struct sun6i_dsi*,struct mipi_dsi_msg const*) ; 
 int /*<<< orphan*/  sun6i_dsi_inst_abort (struct sun6i_dsi*) ; 
 int sun6i_dsi_inst_wait_for_completion (struct sun6i_dsi*) ; 
 int /*<<< orphan*/  sun6i_dsi_start (struct sun6i_dsi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun6i_dsi_dcs_write_long(struct sun6i_dsi *dsi,
				    const struct mipi_dsi_msg *msg)
{
	int ret, len = 0;
	u8 *bounce;
	u16 crc;

	regmap_write(dsi->regs, SUN6I_DSI_CMD_TX_REG(0),
		     sun6i_dsi_dcs_build_pkt_hdr(dsi, msg));

	bounce = kzalloc(msg->tx_len + sizeof(crc), GFP_KERNEL);
	if (!bounce)
		return -ENOMEM;

	memcpy(bounce, msg->tx_buf, msg->tx_len);
	len += msg->tx_len;

	crc = sun6i_dsi_crc_compute(bounce, msg->tx_len);
	memcpy((u8 *)bounce + msg->tx_len, &crc, sizeof(crc));
	len += sizeof(crc);

	regmap_bulk_write(dsi->regs, SUN6I_DSI_CMD_TX_REG(1), bounce, len);
	regmap_write(dsi->regs, SUN6I_DSI_CMD_CTL_REG, len + 4 - 1);
	kfree(bounce);

	sun6i_dsi_start(dsi, DSI_START_LPTX);

	ret = sun6i_dsi_inst_wait_for_completion(dsi);
	if (ret < 0) {
		sun6i_dsi_inst_abort(dsi);
		return ret;
	}

	/*
	 * TODO: There's some bits (reg 0x200, bits 8/9) that
	 * apparently can be used to check whether the data have been
	 * sent, but I couldn't get it to work reliably.
	 */
	return msg->tx_len;
}