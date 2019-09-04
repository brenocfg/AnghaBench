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
struct radeon_encoder_atom_dig {int /*<<< orphan*/ * pin; } ;
struct radeon_encoder {int /*<<< orphan*/  audio; struct radeon_encoder_atom_dig* enc_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  hdmi_funcs; int /*<<< orphan*/  dp_funcs; } ;
struct radeon_device {TYPE_1__ audio; } ;
struct radeon_connector {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {scalar_t__ connector_type; struct drm_device* dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 scalar_t__ CONNECTOR_OBJECT_ID_DISPLAYPORT ; 
 scalar_t__ DRM_MODE_CONNECTOR_DisplayPort ; 
 int connector_status_connected ; 
 scalar_t__ drm_detect_monitor_audio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_audio_chipset_supported (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_audio_enable (struct radeon_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * radeon_audio_get_pin (struct drm_encoder*) ; 
 int /*<<< orphan*/  radeon_connector_edid (struct drm_connector*) ; 
 scalar_t__ radeon_dp_getsinktype (struct radeon_connector*) ; 
 int /*<<< orphan*/  radeon_encoder_is_digital (struct drm_encoder*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void radeon_audio_detect(struct drm_connector *connector,
			 struct drm_encoder *encoder,
			 enum drm_connector_status status)
{
	struct drm_device *dev = connector->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig;

	if (!radeon_audio_chipset_supported(rdev))
		return;

	if (!radeon_encoder_is_digital(encoder))
		return;

	dig = radeon_encoder->enc_priv;

	if (status == connector_status_connected) {
		if (connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) {
			struct radeon_connector *radeon_connector = to_radeon_connector(connector);

			if (radeon_dp_getsinktype(radeon_connector) ==
			    CONNECTOR_OBJECT_ID_DISPLAYPORT)
				radeon_encoder->audio = rdev->audio.dp_funcs;
			else
				radeon_encoder->audio = rdev->audio.hdmi_funcs;
		} else {
			radeon_encoder->audio = rdev->audio.hdmi_funcs;
		}

		if (drm_detect_monitor_audio(radeon_connector_edid(connector))) {
			if (!dig->pin)
				dig->pin = radeon_audio_get_pin(encoder);
			radeon_audio_enable(rdev, dig->pin, 0xf);
		} else {
			radeon_audio_enable(rdev, dig->pin, 0);
			dig->pin = NULL;
		}
	} else {
		radeon_audio_enable(rdev, dig->pin, 0);
		dig->pin = NULL;
	}
}