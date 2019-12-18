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
struct mtk_dsi {scalar_t__ regs; } ;
struct mipi_dsi_msg {int rx_len; scalar_t__ tx_buf; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  type; } ;
struct mipi_dsi_host {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DONE_INT_FLAG ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ DSI_MODE_CTRL ; 
 scalar_t__ DSI_RX_DATA0 ; 
 int EINVAL ; 
 int ETIME ; 
 int /*<<< orphan*/  LPRX_RD_RDY_INT_FLAG ; 
 int MODE ; 
 scalar_t__ MTK_DSI_HOST_IS_READ (int /*<<< orphan*/ ) ; 
 struct mtk_dsi* host_to_dsi (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ mtk_dsi_host_send_cmd (struct mtk_dsi*,struct mipi_dsi_msg const*,int /*<<< orphan*/ ) ; 
 int mtk_dsi_recv_cnt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static ssize_t mtk_dsi_host_transfer(struct mipi_dsi_host *host,
				     const struct mipi_dsi_msg *msg)
{
	struct mtk_dsi *dsi = host_to_dsi(host);
	u32 recv_cnt, i;
	u8 read_data[16];
	void *src_addr;
	u8 irq_flag = CMD_DONE_INT_FLAG;

	if (readl(dsi->regs + DSI_MODE_CTRL) & MODE) {
		DRM_ERROR("dsi engine is not command mode\n");
		return -EINVAL;
	}

	if (MTK_DSI_HOST_IS_READ(msg->type))
		irq_flag |= LPRX_RD_RDY_INT_FLAG;

	if (mtk_dsi_host_send_cmd(dsi, msg, irq_flag) < 0)
		return -ETIME;

	if (!MTK_DSI_HOST_IS_READ(msg->type))
		return 0;

	if (!msg->rx_buf) {
		DRM_ERROR("dsi receive buffer size may be NULL\n");
		return -EINVAL;
	}

	for (i = 0; i < 16; i++)
		*(read_data + i) = readb(dsi->regs + DSI_RX_DATA0 + i);

	recv_cnt = mtk_dsi_recv_cnt(read_data[0], read_data);

	if (recv_cnt > 2)
		src_addr = &read_data[4];
	else
		src_addr = &read_data[1];

	if (recv_cnt > 10)
		recv_cnt = 10;

	if (recv_cnt > msg->rx_len)
		recv_cnt = msg->rx_len;

	if (recv_cnt)
		memcpy(msg->rx_buf, src_addr, recv_cnt);

	DRM_INFO("dsi get %d byte data from the panel address(0x%x)\n",
		 recv_cnt, *((u8 *)(msg->tx_buf)));

	return recv_cnt;
}