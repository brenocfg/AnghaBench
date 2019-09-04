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
struct dw_mipi_dsi {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PKT_STATUS_TIMEOUT_US ; 
 scalar_t__ DSI_CMD_PKT_STATUS ; 
 int /*<<< orphan*/  DSI_GEN_HDR ; 
 int GEN_CMD_EMPTY ; 
 int GEN_CMD_FULL ; 
 int GEN_PLD_W_EMPTY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mipi_dsi_gen_pkt_hdr_write(struct dw_mipi_dsi *dsi, u32 hdr_val)
{
	int ret;
	u32 val, mask;

	ret = readl_poll_timeout(dsi->base + DSI_CMD_PKT_STATUS,
				 val, !(val & GEN_CMD_FULL), 1000,
				 CMD_PKT_STATUS_TIMEOUT_US);
	if (ret) {
		dev_err(dsi->dev, "failed to get available command FIFO\n");
		return ret;
	}

	dsi_write(dsi, DSI_GEN_HDR, hdr_val);

	mask = GEN_CMD_EMPTY | GEN_PLD_W_EMPTY;
	ret = readl_poll_timeout(dsi->base + DSI_CMD_PKT_STATUS,
				 val, (val & mask) == mask,
				 1000, CMD_PKT_STATUS_TIMEOUT_US);
	if (ret) {
		dev_err(dsi->dev, "failed to write command FIFO\n");
		return ret;
	}

	return 0;
}