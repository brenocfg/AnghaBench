#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_mode_fb_cmd {int bpp; scalar_t__ handle; int /*<<< orphan*/  pitch; int /*<<< orphan*/  depth; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  fb_id; } ;
struct drm_framebuffer {TYPE_2__* funcs; int /*<<< orphan*/ * pitches; TYPE_1__* format; int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int (* create_handle ) (struct drm_framebuffer*,struct drm_file*,scalar_t__*) ;} ;
struct TYPE_3__ {int num_planes; int* cpp; int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_framebuffer* drm_framebuffer_lookup (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_framebuffer_put (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_is_current_master (struct drm_file*) ; 
 int stub1 (struct drm_framebuffer*,struct drm_file*,scalar_t__*) ; 

int drm_mode_getfb(struct drm_device *dev,
		   void *data, struct drm_file *file_priv)
{
	struct drm_mode_fb_cmd *r = data;
	struct drm_framebuffer *fb;
	int ret;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EOPNOTSUPP;

	fb = drm_framebuffer_lookup(dev, file_priv, r->fb_id);
	if (!fb)
		return -ENOENT;

	/* Multi-planar framebuffers need getfb2. */
	if (fb->format->num_planes > 1) {
		ret = -EINVAL;
		goto out;
	}

	if (!fb->funcs->create_handle) {
		ret = -ENODEV;
		goto out;
	}

	r->height = fb->height;
	r->width = fb->width;
	r->depth = fb->format->depth;
	r->bpp = fb->format->cpp[0] * 8;
	r->pitch = fb->pitches[0];

	/* GET_FB() is an unprivileged ioctl so we must not return a
	 * buffer-handle to non-master processes! For
	 * backwards-compatibility reasons, we cannot make GET_FB() privileged,
	 * so just return an invalid handle for non-masters.
	 */
	if (!drm_is_current_master(file_priv) && !capable(CAP_SYS_ADMIN)) {
		r->handle = 0;
		ret = 0;
		goto out;
	}

	ret = fb->funcs->create_handle(fb, file_priv, &r->handle);

out:
	drm_framebuffer_put(fb);

	return ret;
}