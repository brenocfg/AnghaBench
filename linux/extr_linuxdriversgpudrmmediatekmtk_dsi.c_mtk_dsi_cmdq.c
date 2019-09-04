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
typedef  size_t u32 ;
struct mtk_dsi {scalar_t__ regs; } ;
struct mipi_dsi_msg {char* tx_buf; int type; int tx_len; } ;

/* Variables and functions */
 int BTA ; 
 size_t CMDQ_SIZE ; 
 size_t CONFIG ; 
 size_t DATA_0 ; 
 size_t DATA_1 ; 
 size_t DATA_ID ; 
 scalar_t__ DSI_CMDQ0 ; 
 scalar_t__ DSI_CMDQ_SIZE ; 
 int LONG_PACKET ; 
 scalar_t__ MTK_DSI_HOST_IS_READ (int) ; 
 int SHORT_PACKET ; 
 int /*<<< orphan*/  mtk_dsi_mask (struct mtk_dsi*,scalar_t__,size_t,int) ; 
 int /*<<< orphan*/  writeb (char const,scalar_t__) ; 

__attribute__((used)) static void mtk_dsi_cmdq(struct mtk_dsi *dsi, const struct mipi_dsi_msg *msg)
{
	const char *tx_buf = msg->tx_buf;
	u8 config, cmdq_size, cmdq_off, type = msg->type;
	u32 reg_val, cmdq_mask, i;

	if (MTK_DSI_HOST_IS_READ(type))
		config = BTA;
	else
		config = (msg->tx_len > 2) ? LONG_PACKET : SHORT_PACKET;

	if (msg->tx_len > 2) {
		cmdq_size = 1 + (msg->tx_len + 3) / 4;
		cmdq_off = 4;
		cmdq_mask = CONFIG | DATA_ID | DATA_0 | DATA_1;
		reg_val = (msg->tx_len << 16) | (type << 8) | config;
	} else {
		cmdq_size = 1;
		cmdq_off = 2;
		cmdq_mask = CONFIG | DATA_ID;
		reg_val = (type << 8) | config;
	}

	for (i = 0; i < msg->tx_len; i++)
		writeb(tx_buf[i], dsi->regs + DSI_CMDQ0 + cmdq_off + i);

	mtk_dsi_mask(dsi, DSI_CMDQ0, cmdq_mask, reg_val);
	mtk_dsi_mask(dsi, DSI_CMDQ_SIZE, CMDQ_SIZE, cmdq_size);
}