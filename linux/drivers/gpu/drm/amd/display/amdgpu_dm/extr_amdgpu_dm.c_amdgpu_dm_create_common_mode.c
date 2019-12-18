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
struct drm_encoder {struct drm_device* dev; } ;
struct drm_display_mode {int hdisplay; int vdisplay; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct drm_device {int dummy; } ;
struct amdgpu_encoder {struct drm_display_mode native_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DISPLAY_MODE_LEN ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 struct drm_display_mode* drm_mode_duplicate (struct drm_device*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static struct drm_display_mode *
amdgpu_dm_create_common_mode(struct drm_encoder *encoder,
			     char *name,
			     int hdisplay, int vdisplay)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct drm_display_mode *mode = NULL;
	struct drm_display_mode *native_mode = &amdgpu_encoder->native_mode;

	mode = drm_mode_duplicate(dev, native_mode);

	if (mode == NULL)
		return NULL;

	mode->hdisplay = hdisplay;
	mode->vdisplay = vdisplay;
	mode->type &= ~DRM_MODE_TYPE_PREFERRED;
	strscpy(mode->name, name, DRM_DISPLAY_MODE_LEN);

	return mode;

}