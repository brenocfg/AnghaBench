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
typedef  enum tegra_dsi_format { ____Placeholder_tegra_dsi_format } tegra_dsi_format ;
typedef  enum mipi_dsi_pixel_format { ____Placeholder_mipi_dsi_pixel_format } mipi_dsi_pixel_format ;

/* Variables and functions */
 int EINVAL ; 
#define  MIPI_DSI_FMT_RGB565 131 
#define  MIPI_DSI_FMT_RGB666 130 
#define  MIPI_DSI_FMT_RGB666_PACKED 129 
#define  MIPI_DSI_FMT_RGB888 128 
 int TEGRA_DSI_FORMAT_16P ; 
 int TEGRA_DSI_FORMAT_18NP ; 
 int TEGRA_DSI_FORMAT_18P ; 
 int TEGRA_DSI_FORMAT_24P ; 

__attribute__((used)) static int tegra_dsi_get_format(enum mipi_dsi_pixel_format format,
				enum tegra_dsi_format *fmt)
{
	switch (format) {
	case MIPI_DSI_FMT_RGB888:
		*fmt = TEGRA_DSI_FORMAT_24P;
		break;

	case MIPI_DSI_FMT_RGB666:
		*fmt = TEGRA_DSI_FORMAT_18NP;
		break;

	case MIPI_DSI_FMT_RGB666_PACKED:
		*fmt = TEGRA_DSI_FORMAT_18P;
		break;

	case MIPI_DSI_FMT_RGB565:
		*fmt = TEGRA_DSI_FORMAT_16P;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}