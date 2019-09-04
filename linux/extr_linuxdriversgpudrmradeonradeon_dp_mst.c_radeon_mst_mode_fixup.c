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
struct radeon_encoder_mst {TYPE_3__* connector; TYPE_2__* primary; int /*<<< orphan*/  pbn; } ;
struct radeon_encoder {struct radeon_encoder_mst* enc_priv; } ;
struct radeon_connector_atom_dig {int /*<<< orphan*/  dp_clock; int /*<<< orphan*/  dp_lane_count; int /*<<< orphan*/  dpcd; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct TYPE_6__ {int devices; struct radeon_connector_atom_dig* con_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  encoder_type; } ;
struct TYPE_5__ {int active_device; int devices; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  drm_dp_calc_pbn_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_dp_max_lane_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_max_link_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_set_crtcinfo (struct drm_display_mode*,int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static bool radeon_mst_mode_fixup(struct drm_encoder *encoder,
				   const struct drm_display_mode *mode,
				   struct drm_display_mode *adjusted_mode)
{
	struct radeon_encoder_mst *mst_enc;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_connector_atom_dig *dig_connector;
	int bpp = 24;

	mst_enc = radeon_encoder->enc_priv;

	mst_enc->pbn = drm_dp_calc_pbn_mode(adjusted_mode->clock, bpp);

	mst_enc->primary->active_device = mst_enc->primary->devices & mst_enc->connector->devices;
	DRM_DEBUG_KMS("setting active device to %08x from %08x %08x for encoder %d\n",
		      mst_enc->primary->active_device, mst_enc->primary->devices,
		      mst_enc->connector->devices, mst_enc->primary->base.encoder_type);


	drm_mode_set_crtcinfo(adjusted_mode, 0);
	dig_connector = mst_enc->connector->con_priv;
	dig_connector->dp_lane_count = drm_dp_max_lane_count(dig_connector->dpcd);
	dig_connector->dp_clock = drm_dp_max_link_rate(dig_connector->dpcd);
	DRM_DEBUG_KMS("dig clock %p %d %d\n", dig_connector,
		      dig_connector->dp_lane_count, dig_connector->dp_clock);
	return true;
}