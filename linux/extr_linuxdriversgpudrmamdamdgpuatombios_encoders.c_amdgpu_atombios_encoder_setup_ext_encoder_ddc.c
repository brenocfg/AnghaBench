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
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTERNAL_ENCODER_ACTION_V3_DDC_SETUP ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_setup_external_encoder (struct drm_encoder*,struct drm_encoder*,int /*<<< orphan*/ ) ; 
 struct drm_encoder* amdgpu_get_external_encoder (struct drm_encoder*) ; 

void
amdgpu_atombios_encoder_setup_ext_encoder_ddc(struct drm_encoder *encoder)
{
	struct drm_encoder *ext_encoder = amdgpu_get_external_encoder(encoder);

	if (ext_encoder)
		/* ddc_setup on the dp bridge */
		amdgpu_atombios_encoder_setup_external_encoder(encoder, ext_encoder,
							EXTERNAL_ENCODER_ACTION_V3_DDC_SETUP);

}