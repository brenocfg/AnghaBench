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
struct mipi_dsi_packet {int payload_length; int /*<<< orphan*/  const* header; int /*<<< orphan*/ * payload; } ;
struct dw_mipi_dsi {int /*<<< orphan*/  dev; scalar_t__ base; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PKT_STATUS_TIMEOUT_US ; 
 scalar_t__ DSI_CMD_PKT_STATUS ; 
 int /*<<< orphan*/  DSI_GEN_PLD_DATA ; 
 int GEN_PLD_W_FULL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dw_mipi_dsi_gen_pkt_hdr_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/  const*,int) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mipi_dsi_write(struct dw_mipi_dsi *dsi,
			     const struct mipi_dsi_packet *packet)
{
	const u8 *tx_buf = packet->payload;
	int len = packet->payload_length, pld_data_bytes = sizeof(u32), ret;
	__le32 word;
	u32 val;

	while (len) {
		if (len < pld_data_bytes) {
			word = 0;
			memcpy(&word, tx_buf, len);
			dsi_write(dsi, DSI_GEN_PLD_DATA, le32_to_cpu(word));
			len = 0;
		} else {
			memcpy(&word, tx_buf, pld_data_bytes);
			dsi_write(dsi, DSI_GEN_PLD_DATA, le32_to_cpu(word));
			tx_buf += pld_data_bytes;
			len -= pld_data_bytes;
		}

		ret = readl_poll_timeout(dsi->base + DSI_CMD_PKT_STATUS,
					 val, !(val & GEN_PLD_W_FULL), 1000,
					 CMD_PKT_STATUS_TIMEOUT_US);
		if (ret) {
			dev_err(dsi->dev,
				"failed to get available write payload FIFO\n");
			return ret;
		}
	}

	word = 0;
	memcpy(&word, packet->header, sizeof(packet->header));
	return dw_mipi_dsi_gen_pkt_hdr_write(dsi, le32_to_cpu(word));
}