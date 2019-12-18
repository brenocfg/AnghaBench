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
struct mipi_dsi_msg {int rx_len; int* rx_buf; } ;
struct dw_mipi_dsi {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PKT_STATUS_TIMEOUT_US ; 
 scalar_t__ DSI_CMD_PKT_STATUS ; 
 int /*<<< orphan*/  DSI_GEN_PLD_DATA ; 
 int GEN_PLD_R_EMPTY ; 
 int GEN_RD_CMD_BUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dsi_read (struct dw_mipi_dsi*,int /*<<< orphan*/ ) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mipi_dsi_read(struct dw_mipi_dsi *dsi,
			    const struct mipi_dsi_msg *msg)
{
	int i, j, ret, len = msg->rx_len;
	u8 *buf = msg->rx_buf;
	u32 val;

	/* Wait end of the read operation */
	ret = readl_poll_timeout(dsi->base + DSI_CMD_PKT_STATUS,
				 val, !(val & GEN_RD_CMD_BUSY),
				 1000, CMD_PKT_STATUS_TIMEOUT_US);
	if (ret) {
		dev_err(dsi->dev, "Timeout during read operation\n");
		return ret;
	}

	for (i = 0; i < len; i += 4) {
		/* Read fifo must not be empty before all bytes are read */
		ret = readl_poll_timeout(dsi->base + DSI_CMD_PKT_STATUS,
					 val, !(val & GEN_PLD_R_EMPTY),
					 1000, CMD_PKT_STATUS_TIMEOUT_US);
		if (ret) {
			dev_err(dsi->dev, "Read payload FIFO is empty\n");
			return ret;
		}

		val = dsi_read(dsi, DSI_GEN_PLD_DATA);
		for (j = 0; j < 4 && j + i < len; j++)
			buf[i + j] = val >> (8 * j);
	}

	return ret;
}