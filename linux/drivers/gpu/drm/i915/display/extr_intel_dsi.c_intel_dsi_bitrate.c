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
struct intel_dsi {int pclk; int lane_count; int /*<<< orphan*/  pixel_format; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 

int intel_dsi_bitrate(const struct intel_dsi *intel_dsi)
{
	int bpp = mipi_dsi_pixel_format_to_bpp(intel_dsi->pixel_format);

	if (WARN_ON(bpp < 0))
		bpp = 16;

	return intel_dsi->pclk * bpp / intel_dsi->lane_count;
}