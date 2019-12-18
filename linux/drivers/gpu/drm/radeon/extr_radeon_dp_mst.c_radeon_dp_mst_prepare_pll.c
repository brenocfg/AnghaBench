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
struct radeon_encoder_mst {TYPE_1__* connector; } ;
struct radeon_encoder {int /*<<< orphan*/  base; struct radeon_encoder_mst* enc_priv; } ;
struct radeon_device {int dummy; } ;
struct radeon_crtc {int bpc; int /*<<< orphan*/  ss; int /*<<< orphan*/  ss_enabled; int /*<<< orphan*/  encoder; } ;
struct radeon_connector_atom_dig {int dp_clock; } ;
struct TYPE_5__ {int bpc; } ;
struct TYPE_6__ {TYPE_2__ display_info; } ;
struct radeon_connector {TYPE_3__ base; int /*<<< orphan*/  pixelclock_for_modeset; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_4__ {struct radeon_connector_atom_dig* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INTERNAL_SS_ON_DP ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,struct radeon_connector_atom_dig*,int) ; 
 int /*<<< orphan*/  radeon_atombios_get_asic_ss_info (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct radeon_connector* radeon_mst_find_connector (int /*<<< orphan*/ *) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 struct radeon_encoder* to_radeon_encoder (int /*<<< orphan*/ ) ; 

void radeon_dp_mst_prepare_pll(struct drm_crtc *crtc, struct drm_display_mode *mode)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(radeon_crtc->encoder);
	struct radeon_encoder_mst *mst_enc = radeon_encoder->enc_priv;
	struct radeon_connector *radeon_connector = radeon_mst_find_connector(&radeon_encoder->base);
	int dp_clock;
	struct radeon_connector_atom_dig *dig_connector = mst_enc->connector->con_priv;

	if (radeon_connector) {
		radeon_connector->pixelclock_for_modeset = mode->clock;
		if (radeon_connector->base.display_info.bpc)
			radeon_crtc->bpc = radeon_connector->base.display_info.bpc;
		else
			radeon_crtc->bpc = 8;
	}

	DRM_DEBUG_KMS("dp_clock %p %d\n", dig_connector, dig_connector->dp_clock);
	dp_clock = dig_connector->dp_clock;
	radeon_crtc->ss_enabled =
		radeon_atombios_get_asic_ss_info(rdev, &radeon_crtc->ss,
						 ASIC_INTERNAL_SS_ON_DP,
						 dp_clock);
}