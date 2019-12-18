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
struct sun6i_dsi {int dummy; } ;
struct mipi_dsi_msg {int type; int tx_len; scalar_t__ tx_buf; } ;

/* Variables and functions */
 scalar_t__ MIPI_DSI_DCS_LONG_WRITE ; 
 int sun6i_dsi_ecc_compute (int) ; 

__attribute__((used)) static u32 sun6i_dsi_dcs_build_pkt_hdr(struct sun6i_dsi *dsi,
				       const struct mipi_dsi_msg *msg)
{
	u32 pkt = msg->type;

	if (msg->type == MIPI_DSI_DCS_LONG_WRITE) {
		pkt |= ((msg->tx_len + 1) & 0xffff) << 8;
		pkt |= (((msg->tx_len + 1) >> 8) & 0xffff) << 16;
	} else {
		pkt |= (((u8 *)msg->tx_buf)[0] << 8);
		if (msg->tx_len > 1)
			pkt |= (((u8 *)msg->tx_buf)[1] << 16);
	}

	pkt |= sun6i_dsi_ecc_compute(pkt) << 24;

	return pkt;
}