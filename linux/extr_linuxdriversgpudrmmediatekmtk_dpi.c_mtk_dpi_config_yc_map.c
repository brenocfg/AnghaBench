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
typedef  enum mtk_dpi_out_yc_map { ____Placeholder_mtk_dpi_out_yc_map } mtk_dpi_out_yc_map ;

/* Variables and functions */
 int /*<<< orphan*/  DPI_OUTPUT_SETTING ; 
#define  MTK_DPI_OUT_YC_MAP_CY 132 
#define  MTK_DPI_OUT_YC_MAP_CYCY 131 
#define  MTK_DPI_OUT_YC_MAP_RGB 130 
#define  MTK_DPI_OUT_YC_MAP_YC 129 
#define  MTK_DPI_OUT_YC_MAP_YCYC 128 
 int YC_MAP ; 
 int YC_MAP_CY ; 
 int YC_MAP_CYCY ; 
 int /*<<< orphan*/  YC_MAP_MASK ; 
 int YC_MAP_RGB ; 
 int YC_MAP_YC ; 
 int YC_MAP_YCYC ; 
 int /*<<< orphan*/  mtk_dpi_mask (struct mtk_dpi*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_dpi_config_yc_map(struct mtk_dpi *dpi,
				  enum mtk_dpi_out_yc_map map)
{
	u32 val;

	switch (map) {
	case MTK_DPI_OUT_YC_MAP_RGB:
		val = YC_MAP_RGB;
		break;
	case MTK_DPI_OUT_YC_MAP_CYCY:
		val = YC_MAP_CYCY;
		break;
	case MTK_DPI_OUT_YC_MAP_YCYC:
		val = YC_MAP_YCYC;
		break;
	case MTK_DPI_OUT_YC_MAP_CY:
		val = YC_MAP_CY;
		break;
	case MTK_DPI_OUT_YC_MAP_YC:
		val = YC_MAP_YC;
		break;
	default:
		val = YC_MAP_RGB;
		break;
	}

	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING, val << YC_MAP, YC_MAP_MASK);
}