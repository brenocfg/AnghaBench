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
struct drm_rect {int x1; int y1; int x2; int y2; } ;
struct TYPE_2__ {int x1; int y1; int x2; int y2; } ;
struct drm_plane_state {TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static bool check_damage_clip(struct drm_plane_state *state, struct drm_rect *r,
			      int x1, int y1, int x2, int y2)
{
	/*
	 * Round down x1/y1 and round up x2/y2. This is because damage is not in
	 * 16.16 fixed point so to catch all pixels.
	 */
	int src_x1 = state->src.x1 >> 16;
	int src_y1 = state->src.y1 >> 16;
	int src_x2 = (state->src.x2 >> 16) + !!(state->src.x2 & 0xFFFF);
	int src_y2 = (state->src.y2 >> 16) + !!(state->src.y2 & 0xFFFF);

	if (x1 >= x2 || y1 >= y2) {
		pr_err("Cannot have damage clip with no dimension.\n");
		return false;
	}

	if (x1 < src_x1 || y1 < src_y1 || x2 > src_x2 || y2 > src_y2) {
		pr_err("Damage cannot be outside rounded plane src.\n");
		return false;
	}

	if (r->x1 != x1 || r->y1 != y1 || r->x2 != x2 || r->y2 != y2) {
		pr_err("Damage = %d %d %d %d\n", r->x1, r->y1, r->x2, r->y2);
		return false;
	}

	return true;
}