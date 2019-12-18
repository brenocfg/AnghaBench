#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ x1; scalar_t__ y1; } ;
struct drm_plane_state {TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_rect_debug_print (char*,TYPE_1__*,int) ; 
 unsigned int drm_rect_height (TYPE_1__*) ; 
 unsigned int drm_rect_width (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

__attribute__((used)) static bool check_src_eq(struct drm_plane_state *plane_state,
			 unsigned src_x, unsigned src_y,
			 unsigned src_w, unsigned src_h)
{
	if (plane_state->src.x1 < 0) {
		pr_err("src x coordinate %x should never be below 0.\n", plane_state->src.x1);
		drm_rect_debug_print("src: ", &plane_state->src, true);
		return false;
	}
	if (plane_state->src.y1 < 0) {
		pr_err("src y coordinate %x should never be below 0.\n", plane_state->src.y1);
		drm_rect_debug_print("src: ", &plane_state->src, true);
		return false;
	}

	if (plane_state->src.x1 != src_x ||
	    plane_state->src.y1 != src_y ||
	    drm_rect_width(&plane_state->src) != src_w ||
	    drm_rect_height(&plane_state->src) != src_h) {
		drm_rect_debug_print("src: ", &plane_state->src, true);
		return false;
	}

	return true;
}