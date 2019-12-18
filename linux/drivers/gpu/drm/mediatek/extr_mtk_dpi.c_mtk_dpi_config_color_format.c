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
struct mtk_dpi {int dummy; } ;
typedef  enum mtk_dpi_out_color_format { ____Placeholder_mtk_dpi_out_color_format } mtk_dpi_out_color_format ;

/* Variables and functions */
 int MTK_DPI_COLOR_FORMAT_YCBCR_422 ; 
 int MTK_DPI_COLOR_FORMAT_YCBCR_422_FULL ; 
 int MTK_DPI_COLOR_FORMAT_YCBCR_444 ; 
 int MTK_DPI_COLOR_FORMAT_YCBCR_444_FULL ; 
 int /*<<< orphan*/  MTK_DPI_OUT_CHANNEL_SWAP_BGR ; 
 int /*<<< orphan*/  MTK_DPI_OUT_CHANNEL_SWAP_RGB ; 
 int /*<<< orphan*/  mtk_dpi_config_channel_swap (struct mtk_dpi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_dpi_config_csc_enable (struct mtk_dpi*,int) ; 
 int /*<<< orphan*/  mtk_dpi_config_swap_input (struct mtk_dpi*,int) ; 
 int /*<<< orphan*/  mtk_dpi_config_yuv422_enable (struct mtk_dpi*,int) ; 

__attribute__((used)) static void mtk_dpi_config_color_format(struct mtk_dpi *dpi,
					enum mtk_dpi_out_color_format format)
{
	if ((format == MTK_DPI_COLOR_FORMAT_YCBCR_444) ||
	    (format == MTK_DPI_COLOR_FORMAT_YCBCR_444_FULL)) {
		mtk_dpi_config_yuv422_enable(dpi, false);
		mtk_dpi_config_csc_enable(dpi, true);
		mtk_dpi_config_swap_input(dpi, false);
		mtk_dpi_config_channel_swap(dpi, MTK_DPI_OUT_CHANNEL_SWAP_BGR);
	} else if ((format == MTK_DPI_COLOR_FORMAT_YCBCR_422) ||
		   (format == MTK_DPI_COLOR_FORMAT_YCBCR_422_FULL)) {
		mtk_dpi_config_yuv422_enable(dpi, true);
		mtk_dpi_config_csc_enable(dpi, true);
		mtk_dpi_config_swap_input(dpi, true);
		mtk_dpi_config_channel_swap(dpi, MTK_DPI_OUT_CHANNEL_SWAP_RGB);
	} else {
		mtk_dpi_config_yuv422_enable(dpi, false);
		mtk_dpi_config_csc_enable(dpi, false);
		mtk_dpi_config_swap_input(dpi, false);
		mtk_dpi_config_channel_swap(dpi, MTK_DPI_OUT_CHANNEL_SWAP_RGB);
	}
}