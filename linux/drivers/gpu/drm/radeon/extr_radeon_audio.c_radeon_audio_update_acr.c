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
struct radeon_hdmi_acr {int dummy; } ;
struct radeon_encoder_atom_dig {TYPE_1__* afmt; } ;
struct radeon_encoder {TYPE_2__* audio; struct radeon_encoder_atom_dig* enc_priv; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* update_acr ) (struct drm_encoder*,int /*<<< orphan*/ ,struct radeon_hdmi_acr const*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 struct radeon_hdmi_acr* radeon_audio_acr (unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,int /*<<< orphan*/ ,struct radeon_hdmi_acr const*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void radeon_audio_update_acr(struct drm_encoder *encoder, unsigned int clock)
{
	const struct radeon_hdmi_acr *acr = radeon_audio_acr(clock);
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

	if (!dig || !dig->afmt)
		return;

	if (radeon_encoder->audio && radeon_encoder->audio->update_acr)
		radeon_encoder->audio->update_acr(encoder, dig->afmt->offset, acr);
}