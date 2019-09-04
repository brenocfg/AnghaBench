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
struct sun6i_dsi {int /*<<< orphan*/  regs; } ;
struct mipi_dsi_msg {int tx_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_START_LPTX ; 
 int /*<<< orphan*/  SUN6I_DSI_CMD_CTL_REG ; 
 int /*<<< orphan*/  SUN6I_DSI_CMD_TX_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sun6i_dsi_dcs_build_pkt_hdr (struct sun6i_dsi*,struct mipi_dsi_msg const*) ; 
 int /*<<< orphan*/  sun6i_dsi_start (struct sun6i_dsi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun6i_dsi_dcs_write_short(struct sun6i_dsi *dsi,
				     const struct mipi_dsi_msg *msg)
{
	regmap_write(dsi->regs, SUN6I_DSI_CMD_TX_REG(0),
		     sun6i_dsi_dcs_build_pkt_hdr(dsi, msg));
	regmap_write_bits(dsi->regs, SUN6I_DSI_CMD_CTL_REG,
			  0xff, (4 - 1));

	sun6i_dsi_start(dsi, DSI_START_LPTX);

	return msg->tx_len;
}