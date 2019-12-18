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
typedef  scalar_t__ const u32 ;
struct dispc_device {TYPE_1__* feat; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;
struct TYPE_2__ {scalar_t__** supported_color_modes; } ;

/* Variables and functions */

__attribute__((used)) static bool dispc_ovl_color_mode_supported(struct dispc_device *dispc,
					   enum omap_plane_id plane, u32 fourcc)
{
	const u32 *modes;
	unsigned int i;

	modes = dispc->feat->supported_color_modes[plane];

	for (i = 0; modes[i]; ++i) {
		if (modes[i] == fourcc)
			return true;
	}

	return false;
}