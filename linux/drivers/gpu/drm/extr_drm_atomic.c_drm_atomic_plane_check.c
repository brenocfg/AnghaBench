#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct drm_plane_state {unsigned int src_w; unsigned int src_x; unsigned int src_h; unsigned int src_y; scalar_t__ crtc_y; scalar_t__ crtc_x; scalar_t__ crtc_h; scalar_t__ crtc_w; struct drm_framebuffer* fb; struct drm_crtc* crtc; struct drm_plane* plane; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct drm_plane {int possible_crtcs; int /*<<< orphan*/  name; TYPE_3__ base; } ;
struct drm_mode_rect {unsigned int x1; unsigned int x2; unsigned int y1; unsigned int y2; } ;
struct drm_framebuffer {int width; int height; int /*<<< orphan*/  modifier; TYPE_2__* format; } ;
struct drm_format_name_buf {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {int /*<<< orphan*/  name; TYPE_1__ base; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int EINVAL ; 
 int ENOSPC ; 
 int ERANGE ; 
 scalar_t__ INT_MAX ; 
 int drm_crtc_mask (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_get_format_name (int /*<<< orphan*/ ,struct drm_format_name_buf*) ; 
 int drm_plane_check_pixel_format (struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_mode_rect* drm_plane_get_damage_clips (struct drm_plane_state const*) ; 
 scalar_t__ drm_plane_get_damage_clips_count (struct drm_plane_state const*) ; 
 scalar_t__ plane_switching_crtc (struct drm_plane_state const*,struct drm_plane_state const*) ; 

__attribute__((used)) static int drm_atomic_plane_check(const struct drm_plane_state *old_plane_state,
				  const struct drm_plane_state *new_plane_state)
{
	struct drm_plane *plane = new_plane_state->plane;
	struct drm_crtc *crtc = new_plane_state->crtc;
	const struct drm_framebuffer *fb = new_plane_state->fb;
	unsigned int fb_width, fb_height;
	struct drm_mode_rect *clips;
	uint32_t num_clips;
	int ret;

	/* either *both* CRTC and FB must be set, or neither */
	if (crtc && !fb) {
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] CRTC set but no FB\n",
				 plane->base.id, plane->name);
		return -EINVAL;
	} else if (fb && !crtc) {
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] FB set but no CRTC\n",
				 plane->base.id, plane->name);
		return -EINVAL;
	}

	/* if disabled, we don't care about the rest of the state: */
	if (!crtc)
		return 0;

	/* Check whether this plane is usable on this CRTC */
	if (!(plane->possible_crtcs & drm_crtc_mask(crtc))) {
		DRM_DEBUG_ATOMIC("Invalid [CRTC:%d:%s] for [PLANE:%d:%s]\n",
				 crtc->base.id, crtc->name,
				 plane->base.id, plane->name);
		return -EINVAL;
	}

	/* Check whether this plane supports the fb pixel format. */
	ret = drm_plane_check_pixel_format(plane, fb->format->format,
					   fb->modifier);
	if (ret) {
		struct drm_format_name_buf format_name;
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] invalid pixel format %s, modifier 0x%llx\n",
				 plane->base.id, plane->name,
				 drm_get_format_name(fb->format->format,
						     &format_name),
				 fb->modifier);
		return ret;
	}

	/* Give drivers some help against integer overflows */
	if (new_plane_state->crtc_w > INT_MAX ||
	    new_plane_state->crtc_x > INT_MAX - (int32_t) new_plane_state->crtc_w ||
	    new_plane_state->crtc_h > INT_MAX ||
	    new_plane_state->crtc_y > INT_MAX - (int32_t) new_plane_state->crtc_h) {
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] invalid CRTC coordinates %ux%u+%d+%d\n",
				 plane->base.id, plane->name,
				 new_plane_state->crtc_w, new_plane_state->crtc_h,
				 new_plane_state->crtc_x, new_plane_state->crtc_y);
		return -ERANGE;
	}

	fb_width = fb->width << 16;
	fb_height = fb->height << 16;

	/* Make sure source coordinates are inside the fb. */
	if (new_plane_state->src_w > fb_width ||
	    new_plane_state->src_x > fb_width - new_plane_state->src_w ||
	    new_plane_state->src_h > fb_height ||
	    new_plane_state->src_y > fb_height - new_plane_state->src_h) {
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] invalid source coordinates "
				 "%u.%06ux%u.%06u+%u.%06u+%u.%06u (fb %ux%u)\n",
				 plane->base.id, plane->name,
				 new_plane_state->src_w >> 16,
				 ((new_plane_state->src_w & 0xffff) * 15625) >> 10,
				 new_plane_state->src_h >> 16,
				 ((new_plane_state->src_h & 0xffff) * 15625) >> 10,
				 new_plane_state->src_x >> 16,
				 ((new_plane_state->src_x & 0xffff) * 15625) >> 10,
				 new_plane_state->src_y >> 16,
				 ((new_plane_state->src_y & 0xffff) * 15625) >> 10,
				 fb->width, fb->height);
		return -ENOSPC;
	}

	clips = drm_plane_get_damage_clips(new_plane_state);
	num_clips = drm_plane_get_damage_clips_count(new_plane_state);

	/* Make sure damage clips are valid and inside the fb. */
	while (num_clips > 0) {
		if (clips->x1 >= clips->x2 ||
		    clips->y1 >= clips->y2 ||
		    clips->x1 < 0 ||
		    clips->y1 < 0 ||
		    clips->x2 > fb_width ||
		    clips->y2 > fb_height) {
			DRM_DEBUG_ATOMIC("[PLANE:%d:%s] invalid damage clip %d %d %d %d\n",
					 plane->base.id, plane->name, clips->x1,
					 clips->y1, clips->x2, clips->y2);
			return -EINVAL;
		}
		clips++;
		num_clips--;
	}

	if (plane_switching_crtc(old_plane_state, new_plane_state)) {
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] switching CRTC directly\n",
				 plane->base.id, plane->name);
		return -EINVAL;
	}

	return 0;
}