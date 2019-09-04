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
struct intel_vgpu_cursor_plane_format {scalar_t__ x_hot; scalar_t__ width; scalar_t__ y_hot; scalar_t__ height; } ;

/* Variables and functions */

__attribute__((used)) static bool validate_hotspot(struct intel_vgpu_cursor_plane_format *c)
{
	if (c && c->x_hot <= c->width && c->y_hot <= c->height)
		return true;
	else
		return false;
}