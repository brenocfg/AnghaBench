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
struct drm_encoder {int possible_crtcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  subpixel_order; } ;
struct drm_connector {int interlace_allowed; int doublescan_allowed; TYPE_1__ display_info; } ;
struct amdgpu_device {int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VIRTUAL ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_VIRTUAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SubPixelHorizontalRGB ; 
 int /*<<< orphan*/  dce_virtual_connector_funcs ; 
 int /*<<< orphan*/  dce_virtual_connector_helper_funcs ; 
 int /*<<< orphan*/  dce_virtual_encoder_funcs ; 
 int /*<<< orphan*/  dce_virtual_encoder_helper_funcs ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_register (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (int /*<<< orphan*/ ,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_encoder*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dce_virtual_connector_encoder_init(struct amdgpu_device *adev,
					      int index)
{
	struct drm_encoder *encoder;
	struct drm_connector *connector;

	/* add a new encoder */
	encoder = kzalloc(sizeof(struct drm_encoder), GFP_KERNEL);
	if (!encoder)
		return -ENOMEM;
	encoder->possible_crtcs = 1 << index;
	drm_encoder_init(adev->ddev, encoder, &dce_virtual_encoder_funcs,
			 DRM_MODE_ENCODER_VIRTUAL, NULL);
	drm_encoder_helper_add(encoder, &dce_virtual_encoder_helper_funcs);

	connector = kzalloc(sizeof(struct drm_connector), GFP_KERNEL);
	if (!connector) {
		kfree(encoder);
		return -ENOMEM;
	}

	/* add a new connector */
	drm_connector_init(adev->ddev, connector, &dce_virtual_connector_funcs,
			   DRM_MODE_CONNECTOR_VIRTUAL);
	drm_connector_helper_add(connector, &dce_virtual_connector_helper_funcs);
	connector->display_info.subpixel_order = SubPixelHorizontalRGB;
	connector->interlace_allowed = false;
	connector->doublescan_allowed = false;
	drm_connector_register(connector);

	/* link them */
	drm_connector_attach_encoder(connector, encoder);

	return 0;
}