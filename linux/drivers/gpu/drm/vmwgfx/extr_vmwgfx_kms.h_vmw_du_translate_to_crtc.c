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
struct drm_rect {int dummy; } ;
struct drm_plane_state {int src_x; int crtc_x; int src_y; int crtc_y; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_rect_translate (struct drm_rect*,int,int) ; 

__attribute__((used)) static inline void vmw_du_translate_to_crtc(struct drm_plane_state *state,
					    struct drm_rect *r)
{
	int translate_crtc_x = -((state->src_x >> 16) - state->crtc_x);
	int translate_crtc_y = -((state->src_y >> 16) - state->crtc_y);

	drm_rect_translate(r, translate_crtc_x, translate_crtc_y);
}