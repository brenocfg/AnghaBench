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
 int /*<<< orphan*/  atombios_external_encoder_setup (struct drm_encoder*,struct drm_encoder*,int /*<<< orphan*/ ) ; 
 struct drm_encoder* radeon_get_external_encoder (struct drm_encoder*) ; 

void
radeon_atom_ext_encoder_setup_ddc(struct drm_encoder *encoder)
{
	struct drm_encoder *ext_encoder = radeon_get_external_encoder(encoder);

	if (ext_encoder)
		/* ddc_setup on the dp bridge */
		atombios_external_encoder_setup(encoder, ext_encoder,
						EXTERNAL_ENCODER_ACTION_V3_DDC_SETUP);

}