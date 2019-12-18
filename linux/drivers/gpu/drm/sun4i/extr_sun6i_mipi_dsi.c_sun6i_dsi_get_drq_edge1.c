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
typedef  scalar_t__ u16 ;
struct sun6i_dsi {struct mipi_dsi_device* device; } ;
struct mipi_dsi_device {unsigned int lanes; int /*<<< orphan*/  format; } ;
struct drm_display_mode {unsigned int htotal; unsigned int hsync_end; unsigned int hdisplay; } ;

/* Variables and functions */
 scalar_t__ SUN6I_DSI_SYNC_POINT ; 
 int mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 sun6i_dsi_get_drq_edge1(struct sun6i_dsi *dsi,
				   struct drm_display_mode *mode,
				   u16 line_num)
{
	struct mipi_dsi_device *device = dsi->device;
	unsigned int Bpp = mipi_dsi_pixel_format_to_bpp(device->format) / 8;
	unsigned int hbp = mode->htotal - mode->hsync_end;
	u16 edge1;

	edge1 = SUN6I_DSI_SYNC_POINT;
	edge1 += (mode->hdisplay + hbp + 20) * Bpp / device->lanes;

	if (edge1 > line_num)
		return line_num;

	return edge1;
}