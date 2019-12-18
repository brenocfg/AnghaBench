#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int hactive; } ;
struct mtk_dsi {int format; scalar_t__ regs; TYPE_1__ vm; } ;

/* Variables and functions */
 scalar_t__ DSI_PSCTRL ; 
 int DSI_PS_WC ; 
 int LOOSELY_PS_18BIT_RGB666 ; 
#define  MIPI_DSI_FMT_RGB565 131 
#define  MIPI_DSI_FMT_RGB666 130 
#define  MIPI_DSI_FMT_RGB666_PACKED 129 
#define  MIPI_DSI_FMT_RGB888 128 
 int PACKED_PS_16BIT_RGB565 ; 
 int PACKED_PS_18BIT_RGB666 ; 
 int PACKED_PS_24BIT_RGB888 ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtk_dsi_ps_control(struct mtk_dsi *dsi)
{
	u32 dsi_tmp_buf_bpp;
	u32 tmp_reg;

	switch (dsi->format) {
	case MIPI_DSI_FMT_RGB888:
		tmp_reg = PACKED_PS_24BIT_RGB888;
		dsi_tmp_buf_bpp = 3;
		break;
	case MIPI_DSI_FMT_RGB666:
		tmp_reg = LOOSELY_PS_18BIT_RGB666;
		dsi_tmp_buf_bpp = 3;
		break;
	case MIPI_DSI_FMT_RGB666_PACKED:
		tmp_reg = PACKED_PS_18BIT_RGB666;
		dsi_tmp_buf_bpp = 3;
		break;
	case MIPI_DSI_FMT_RGB565:
		tmp_reg = PACKED_PS_16BIT_RGB565;
		dsi_tmp_buf_bpp = 2;
		break;
	default:
		tmp_reg = PACKED_PS_24BIT_RGB888;
		dsi_tmp_buf_bpp = 3;
		break;
	}

	tmp_reg += dsi->vm.hactive * dsi_tmp_buf_bpp & DSI_PS_WC;
	writel(tmp_reg, dsi->regs + DSI_PSCTRL);
}