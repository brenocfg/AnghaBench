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
typedef  enum mtk_dpi_out_bit_num { ____Placeholder_mtk_dpi_out_bit_num } mtk_dpi_out_bit_num ;

/* Variables and functions */
 int /*<<< orphan*/  DPI_OUTPUT_SETTING ; 
#define  MTK_DPI_OUT_BIT_NUM_10BITS 131 
#define  MTK_DPI_OUT_BIT_NUM_12BITS 130 
#define  MTK_DPI_OUT_BIT_NUM_16BITS 129 
#define  MTK_DPI_OUT_BIT_NUM_8BITS 128 
 int OUT_BIT ; 
 int OUT_BIT_10 ; 
 int OUT_BIT_12 ; 
 int OUT_BIT_16 ; 
 int OUT_BIT_8 ; 
 int /*<<< orphan*/  OUT_BIT_MASK ; 
 int /*<<< orphan*/  mtk_dpi_mask (struct mtk_dpi*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_dpi_config_bit_num(struct mtk_dpi *dpi,
				   enum mtk_dpi_out_bit_num num)
{
	u32 val;

	switch (num) {
	case MTK_DPI_OUT_BIT_NUM_8BITS:
		val = OUT_BIT_8;
		break;
	case MTK_DPI_OUT_BIT_NUM_10BITS:
		val = OUT_BIT_10;
		break;
	case MTK_DPI_OUT_BIT_NUM_12BITS:
		val = OUT_BIT_12;
		break;
	case MTK_DPI_OUT_BIT_NUM_16BITS:
		val = OUT_BIT_16;
		break;
	default:
		val = OUT_BIT_8;
		break;
	}
	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING, val << OUT_BIT,
		     OUT_BIT_MASK);
}