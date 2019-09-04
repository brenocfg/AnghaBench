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
typedef  int u32 ;
struct mipi_dsi_msg {int tx_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * tx_buf; } ;
struct dw_mipi_dsi {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PKT_STATUS_TIMEOUT_US ; 
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ DSI_CMD_PKT_STATUS ; 
 int /*<<< orphan*/  DSI_GEN_PLD_DATA ; 
 int EINVAL ; 
 int GEN_HDATA (int) ; 
 int GEN_HTYPE (int /*<<< orphan*/ ) ; 
 int GEN_PLD_W_FULL ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int) ; 
 int dw_mipi_dsi_gen_pkt_hdr_write (struct dw_mipi_dsi*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mipi_dsi_dcs_long_write(struct dw_mipi_dsi *dsi,
				      const struct mipi_dsi_msg *msg)
{
	const u8 *tx_buf = msg->tx_buf;
	int len = msg->tx_len, pld_data_bytes = sizeof(u32), ret;
	u32 hdr_val = GEN_HDATA(msg->tx_len) | GEN_HTYPE(msg->type);
	u32 remainder;
	u32 val;

	if (msg->tx_len < 3) {
		DRM_DEV_ERROR(dsi->dev,
			      "wrong tx buf length %zu for long write\n",
			      msg->tx_len);
		return -EINVAL;
	}

	while (DIV_ROUND_UP(len, pld_data_bytes)) {
		if (len < pld_data_bytes) {
			remainder = 0;
			memcpy(&remainder, tx_buf, len);
			dsi_write(dsi, DSI_GEN_PLD_DATA, remainder);
			len = 0;
		} else {
			memcpy(&remainder, tx_buf, pld_data_bytes);
			dsi_write(dsi, DSI_GEN_PLD_DATA, remainder);
			tx_buf += pld_data_bytes;
			len -= pld_data_bytes;
		}

		ret = readl_poll_timeout(dsi->base + DSI_CMD_PKT_STATUS,
					 val, !(val & GEN_PLD_W_FULL), 1000,
					 CMD_PKT_STATUS_TIMEOUT_US);
		if (ret < 0) {
			DRM_DEV_ERROR(dsi->dev,
				      "failed to get available write payload FIFO\n");
			return ret;
		}
	}

	return dw_mipi_dsi_gen_pkt_hdr_write(dsi, hdr_val);
}