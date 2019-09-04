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
struct nouveau_framebuffer {int /*<<< orphan*/  base; struct nouveau_bo* nvbo; } ;
struct TYPE_4__ {scalar_t__ family; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
struct TYPE_6__ {TYPE_2__ device; } ;
struct nouveau_drm {TYPE_3__ client; } ;
struct nouveau_bo {int dummy; } ;
struct drm_mode_fb_cmd2 {scalar_t__ pixel_format; int* pitches; } ;
struct drm_format_name_buf {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ DRM_FORMAT_NV12 ; 
 scalar_t__ DRM_FORMAT_NV21 ; 
 scalar_t__ DRM_FORMAT_UYVY ; 
 scalar_t__ DRM_FORMAT_YUYV ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 int drm_framebuffer_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_get_format_name (scalar_t__,struct drm_format_name_buf*) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,int /*<<< orphan*/ *,struct drm_mode_fb_cmd2 const*) ; 
 int /*<<< orphan*/  kfree (struct nouveau_framebuffer*) ; 
 struct nouveau_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_framebuffer_funcs ; 

int
nouveau_framebuffer_new(struct drm_device *dev,
			const struct drm_mode_fb_cmd2 *mode_cmd,
			struct nouveau_bo *nvbo,
			struct nouveau_framebuffer **pfb)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_framebuffer *fb;
	int ret;

        /* YUV overlays have special requirements pre-NV50 */
	if (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA &&

	    (mode_cmd->pixel_format == DRM_FORMAT_YUYV ||
	     mode_cmd->pixel_format == DRM_FORMAT_UYVY ||
	     mode_cmd->pixel_format == DRM_FORMAT_NV12 ||
	     mode_cmd->pixel_format == DRM_FORMAT_NV21) &&
	    (mode_cmd->pitches[0] & 0x3f || /* align 64 */
	     mode_cmd->pitches[0] >= 0x10000 || /* at most 64k pitch */
	     (mode_cmd->pitches[1] && /* pitches for planes must match */
	      mode_cmd->pitches[0] != mode_cmd->pitches[1]))) {
		struct drm_format_name_buf format_name;
		DRM_DEBUG_KMS("Unsuitable framebuffer: format: %s; pitches: 0x%x\n 0x%x\n",
			      drm_get_format_name(mode_cmd->pixel_format,
						  &format_name),
			      mode_cmd->pitches[0],
			      mode_cmd->pitches[1]);
		return -EINVAL;
	}

	if (!(fb = *pfb = kzalloc(sizeof(*fb), GFP_KERNEL)))
		return -ENOMEM;

	drm_helper_mode_fill_fb_struct(dev, &fb->base, mode_cmd);
	fb->nvbo = nvbo;

	ret = drm_framebuffer_init(dev, &fb->base, &nouveau_framebuffer_funcs);
	if (ret)
		kfree(fb);
	return ret;
}