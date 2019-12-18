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
struct mtk_dpi {int dummy; } ;
typedef  enum mtk_dpi_out_channel_swap { ____Placeholder_mtk_dpi_out_channel_swap } mtk_dpi_out_channel_swap ;

/* Variables and functions */
 int CH_SWAP ; 
 int /*<<< orphan*/  CH_SWAP_MASK ; 
 int /*<<< orphan*/  DPI_OUTPUT_SETTING ; 
#define  MTK_DPI_OUT_CHANNEL_SWAP_BGR 133 
#define  MTK_DPI_OUT_CHANNEL_SWAP_BRG 132 
#define  MTK_DPI_OUT_CHANNEL_SWAP_GBR 131 
#define  MTK_DPI_OUT_CHANNEL_SWAP_GRB 130 
#define  MTK_DPI_OUT_CHANNEL_SWAP_RBG 129 
#define  MTK_DPI_OUT_CHANNEL_SWAP_RGB 128 
 int SWAP_BGR ; 
 int SWAP_BRG ; 
 int SWAP_GBR ; 
 int SWAP_GRB ; 
 int SWAP_RBG ; 
 int SWAP_RGB ; 
 int /*<<< orphan*/  mtk_dpi_mask (struct mtk_dpi*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_dpi_config_channel_swap(struct mtk_dpi *dpi,
					enum mtk_dpi_out_channel_swap swap)
{
	u32 val;

	switch (swap) {
	case MTK_DPI_OUT_CHANNEL_SWAP_RGB:
		val = SWAP_RGB;
		break;
	case MTK_DPI_OUT_CHANNEL_SWAP_GBR:
		val = SWAP_GBR;
		break;
	case MTK_DPI_OUT_CHANNEL_SWAP_BRG:
		val = SWAP_BRG;
		break;
	case MTK_DPI_OUT_CHANNEL_SWAP_RBG:
		val = SWAP_RBG;
		break;
	case MTK_DPI_OUT_CHANNEL_SWAP_GRB:
		val = SWAP_GRB;
		break;
	case MTK_DPI_OUT_CHANNEL_SWAP_BGR:
		val = SWAP_BGR;
		break;
	default:
		val = SWAP_RGB;
		break;
	}

	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING, val << CH_SWAP, CH_SWAP_MASK);
}