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
struct msm_dsi_host {int /*<<< orphan*/ * rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_DSI_RDBK_DATA (int) ; 
 int dsi_read (struct msm_dsi_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int) ; 

__attribute__((used)) static int dsi_cmd_dma_rx(struct msm_dsi_host *msm_host,
			u8 *buf, int rx_byte, int pkt_size)
{
	u32 *lp, *temp, data;
	int i, j = 0, cnt;
	u32 read_cnt;
	u8 reg[16];
	int repeated_bytes = 0;
	int buf_offset = buf - msm_host->rx_buf;

	lp = (u32 *)buf;
	temp = (u32 *)reg;
	cnt = (rx_byte + 3) >> 2;
	if (cnt > 4)
		cnt = 4; /* 4 x 32 bits registers only */

	if (rx_byte == 4)
		read_cnt = 4;
	else
		read_cnt = pkt_size + 6;

	/*
	 * In case of multiple reads from the panel, after the first read, there
	 * is possibility that there are some bytes in the payload repeating in
	 * the RDBK_DATA registers. Since we read all the parameters from the
	 * panel right from the first byte for every pass. We need to skip the
	 * repeating bytes and then append the new parameters to the rx buffer.
	 */
	if (read_cnt > 16) {
		int bytes_shifted;
		/* Any data more than 16 bytes will be shifted out.
		 * The temp read buffer should already contain these bytes.
		 * The remaining bytes in read buffer are the repeated bytes.
		 */
		bytes_shifted = read_cnt - 16;
		repeated_bytes = buf_offset - bytes_shifted;
	}

	for (i = cnt - 1; i >= 0; i--) {
		data = dsi_read(msm_host, REG_DSI_RDBK_DATA(i));
		*temp++ = ntohl(data); /* to host byte order */
		DBG("data = 0x%x and ntohl(data) = 0x%x", data, ntohl(data));
	}

	for (i = repeated_bytes; i < 16; i++)
		buf[j++] = reg[i];

	return j;
}