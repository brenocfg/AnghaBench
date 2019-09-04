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
typedef  int /*<<< orphan*/  u32 ;
struct dispc_device {TYPE_1__* feat; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;
struct TYPE_2__ {int /*<<< orphan*/  const** supported_color_modes; } ;

/* Variables and functions */

__attribute__((used)) static const u32 *dispc_ovl_get_color_modes(struct dispc_device *dispc,
					    enum omap_plane_id plane)
{
	return dispc->feat->supported_color_modes[plane];
}