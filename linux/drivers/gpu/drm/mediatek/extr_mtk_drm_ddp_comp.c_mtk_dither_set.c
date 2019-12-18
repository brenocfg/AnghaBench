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
struct mtk_ddp_comp {scalar_t__ regs; } ;

/* Variables and functions */
 int DISP_DITHERING ; 
 scalar_t__ DISP_DITHER_15 ; 
 scalar_t__ DISP_DITHER_16 ; 
 scalar_t__ DISP_DITHER_5 ; 
 scalar_t__ DISP_DITHER_7 ; 
 int DITHER_ADD_LSHIFT_B (scalar_t__) ; 
 int DITHER_ADD_LSHIFT_G (scalar_t__) ; 
 int DITHER_ADD_LSHIFT_R (scalar_t__) ; 
 int DITHER_LSB_ERR_SHIFT_B (scalar_t__) ; 
 int DITHER_LSB_ERR_SHIFT_G (scalar_t__) ; 
 int DITHER_LSB_ERR_SHIFT_R (scalar_t__) ; 
 int DITHER_NEW_BIT_MODE ; 
 scalar_t__ MTK_MAX_BPC ; 
 unsigned int MTK_MIN_BPC ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void mtk_dither_set(struct mtk_ddp_comp *comp, unsigned int bpc,
		    unsigned int CFG)
{
	/* If bpc equal to 0, the dithering function didn't be enabled */
	if (bpc == 0)
		return;

	if (bpc >= MTK_MIN_BPC) {
		writel(0, comp->regs + DISP_DITHER_5);
		writel(0, comp->regs + DISP_DITHER_7);
		writel(DITHER_LSB_ERR_SHIFT_R(MTK_MAX_BPC - bpc) |
		       DITHER_ADD_LSHIFT_R(MTK_MAX_BPC - bpc) |
		       DITHER_NEW_BIT_MODE,
		       comp->regs + DISP_DITHER_15);
		writel(DITHER_LSB_ERR_SHIFT_B(MTK_MAX_BPC - bpc) |
		       DITHER_ADD_LSHIFT_B(MTK_MAX_BPC - bpc) |
		       DITHER_LSB_ERR_SHIFT_G(MTK_MAX_BPC - bpc) |
		       DITHER_ADD_LSHIFT_G(MTK_MAX_BPC - bpc),
		       comp->regs + DISP_DITHER_16);
		writel(DISP_DITHERING, comp->regs + CFG);
	}
}