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
typedef  int u8 ;
typedef  int u32 ;
struct radeon_encoder_atom_dig {TYPE_1__* pin; int /*<<< orphan*/  afmt; } ;
struct radeon_encoder {struct radeon_encoder_atom_dig* enc_priv; } ;
struct radeon_device {int dummy; } ;
struct drm_encoder {TYPE_2__* dev; } ;
struct TYPE_4__ {struct radeon_device* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZ_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER ; 
 int DP_CONNECTION ; 
 int HDMI_CONNECTION ; 
 int RREG32_ENDPOINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SPEAKER_ALLOCATION (int) ; 
 int SPEAKER_ALLOCATION_MASK ; 
 int /*<<< orphan*/  WREG32_ENDPOINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void dce6_afmt_hdmi_write_speaker_allocation(struct drm_encoder *encoder,
					     u8 *sadb, int sad_count)
{
	struct radeon_device *rdev = encoder->dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	u32 tmp;

	if (!dig || !dig->afmt || !dig->pin)
		return;

	/* program the speaker allocation */
	tmp = RREG32_ENDPOINT(dig->pin->offset,
			      AZ_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER);
	tmp &= ~(DP_CONNECTION | SPEAKER_ALLOCATION_MASK);
	/* set HDMI mode */
	tmp |= HDMI_CONNECTION;
	if (sad_count)
		tmp |= SPEAKER_ALLOCATION(sadb[0]);
	else
		tmp |= SPEAKER_ALLOCATION(5); /* stereo */
	WREG32_ENDPOINT(dig->pin->offset,
			AZ_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER, tmp);
}