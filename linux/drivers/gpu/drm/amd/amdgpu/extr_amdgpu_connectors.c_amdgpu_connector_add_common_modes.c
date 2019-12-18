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
struct drm_display_mode {int hdisplay; int vdisplay; } ;
struct drm_device {int dummy; } ;
struct drm_connector {int dummy; } ;
struct amdgpu_encoder {int devices; struct drm_display_mode native_mode; } ;

/* Variables and functions */
 int ATOM_DEVICE_LCD_SUPPORT ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 struct drm_display_mode* drm_cvt_mode (struct drm_device*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void amdgpu_connector_add_common_modes(struct drm_encoder *encoder,
					       struct drm_connector *connector)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct drm_display_mode *mode = NULL;
	struct drm_display_mode *native_mode = &amdgpu_encoder->native_mode;
	int i;
	static const struct mode_size {
		int w;
		int h;
	} common_modes[17] = {
		{ 640,  480},
		{ 720,  480},
		{ 800,  600},
		{ 848,  480},
		{1024,  768},
		{1152,  768},
		{1280,  720},
		{1280,  800},
		{1280,  854},
		{1280,  960},
		{1280, 1024},
		{1440,  900},
		{1400, 1050},
		{1680, 1050},
		{1600, 1200},
		{1920, 1080},
		{1920, 1200}
	};

	for (i = 0; i < 17; i++) {
		if (amdgpu_encoder->devices & (ATOM_DEVICE_TV_SUPPORT)) {
			if (common_modes[i].w > 1024 ||
			    common_modes[i].h > 768)
				continue;
		}
		if (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) {
			if (common_modes[i].w > native_mode->hdisplay ||
			    common_modes[i].h > native_mode->vdisplay ||
			    (common_modes[i].w == native_mode->hdisplay &&
			     common_modes[i].h == native_mode->vdisplay))
				continue;
		}
		if (common_modes[i].w < 320 || common_modes[i].h < 200)
			continue;

		mode = drm_cvt_mode(dev, common_modes[i].w, common_modes[i].h, 60, false, false, false);
		drm_mode_probed_add(connector, mode);
	}
}