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
typedef  int u8 ;
typedef  int u32 ;
struct sun6i_dsi {int /*<<< orphan*/  regs; } ;
struct mipi_dsi_msg {scalar_t__ rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_START_LPRX ; 
 int EIO ; 
 int MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT ; 
 int /*<<< orphan*/  SUN6I_DSI_CMD_CTL_REG ; 
 int SUN6I_DSI_CMD_CTL_RX_OVERFLOW ; 
 int /*<<< orphan*/  SUN6I_DSI_CMD_RX_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN6I_DSI_CMD_TX_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sun6i_dsi_dcs_build_pkt_hdr (struct sun6i_dsi*,struct mipi_dsi_msg const*) ; 
 int /*<<< orphan*/  sun6i_dsi_inst_abort (struct sun6i_dsi*) ; 
 int sun6i_dsi_inst_wait_for_completion (struct sun6i_dsi*) ; 
 int /*<<< orphan*/  sun6i_dsi_start (struct sun6i_dsi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun6i_dsi_dcs_read(struct sun6i_dsi *dsi,
			      const struct mipi_dsi_msg *msg)
{
	u32 val;
	int ret;
	u8 byte0;

	regmap_write(dsi->regs, SUN6I_DSI_CMD_TX_REG(0),
		     sun6i_dsi_dcs_build_pkt_hdr(dsi, msg));
	regmap_write(dsi->regs, SUN6I_DSI_CMD_CTL_REG,
		     (4 - 1));

	sun6i_dsi_start(dsi, DSI_START_LPRX);

	ret = sun6i_dsi_inst_wait_for_completion(dsi);
	if (ret < 0) {
		sun6i_dsi_inst_abort(dsi);
		return ret;
	}

	/*
	 * TODO: There's some bits (reg 0x200, bits 24/25) that
	 * apparently can be used to check whether the data have been
	 * received, but I couldn't get it to work reliably.
	 */
	regmap_read(dsi->regs, SUN6I_DSI_CMD_CTL_REG, &val);
	if (val & SUN6I_DSI_CMD_CTL_RX_OVERFLOW)
		return -EIO;

	regmap_read(dsi->regs, SUN6I_DSI_CMD_RX_REG(0), &val);
	byte0 = val & 0xff;
	if (byte0 == MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT)
		return -EIO;

	((u8 *)msg->rx_buf)[0] = (val >> 8);

	return 1;
}