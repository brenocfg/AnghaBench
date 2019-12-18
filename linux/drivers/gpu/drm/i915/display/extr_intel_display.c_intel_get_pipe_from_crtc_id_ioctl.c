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
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct drm_i915_get_pipe_from_crtc_id {int /*<<< orphan*/  pipe; int /*<<< orphan*/  crtc_id; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct drm_crtc* drm_crtc_find (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

int intel_get_pipe_from_crtc_id_ioctl(struct drm_device *dev, void *data,
				      struct drm_file *file)
{
	struct drm_i915_get_pipe_from_crtc_id *pipe_from_crtc_id = data;
	struct drm_crtc *drmmode_crtc;
	struct intel_crtc *crtc;

	drmmode_crtc = drm_crtc_find(dev, file, pipe_from_crtc_id->crtc_id);
	if (!drmmode_crtc)
		return -ENOENT;

	crtc = to_intel_crtc(drmmode_crtc);
	pipe_from_crtc_id->pipe = crtc->pipe;

	return 0;
}