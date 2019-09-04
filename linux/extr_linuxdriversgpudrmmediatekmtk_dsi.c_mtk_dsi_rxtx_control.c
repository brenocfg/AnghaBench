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
struct mtk_dsi {int lanes; int mode_flags; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ DSI_TXRX_CTRL ; 
 int MIPI_DSI_CLOCK_NON_CONTINUOUS ; 
 int MIPI_DSI_MODE_EOT_PACKET ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtk_dsi_rxtx_control(struct mtk_dsi *dsi)
{
	u32 tmp_reg;

	switch (dsi->lanes) {
	case 1:
		tmp_reg = 1 << 2;
		break;
	case 2:
		tmp_reg = 3 << 2;
		break;
	case 3:
		tmp_reg = 7 << 2;
		break;
	case 4:
		tmp_reg = 0xf << 2;
		break;
	default:
		tmp_reg = 0xf << 2;
		break;
	}

	tmp_reg |= (dsi->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS) << 6;
	tmp_reg |= (dsi->mode_flags & MIPI_DSI_MODE_EOT_PACKET) >> 3;

	writel(tmp_reg, dsi->regs + DSI_TXRX_CTRL);
}