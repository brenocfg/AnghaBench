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
typedef  int u32 ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_encoder_atom_dig {int /*<<< orphan*/  afmt; } ;
struct amdgpu_encoder {struct amdgpu_encoder_atom_dig* enc_priv; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_crtc {int /*<<< orphan*/  crtc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCG_AUDIO_DTO0_SOURCE_SEL ; 
 int /*<<< orphan*/  DCCG_AUDIO_DTO_SOURCE ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmDCCG_AUDIO_DTO0_MODULE ; 
 int /*<<< orphan*/  mmDCCG_AUDIO_DTO0_PHASE ; 
 int /*<<< orphan*/  mmDCCG_AUDIO_DTO_SOURCE ; 
 struct amdgpu_crtc* to_amdgpu_crtc (int /*<<< orphan*/ ) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void dce_v10_0_audio_set_dto(struct drm_encoder *encoder, u32 clock)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
	u32 dto_phase = 24 * 1000;
	u32 dto_modulo = clock;
	u32 tmp;

	if (!dig || !dig->afmt)
		return;

	/* XXX two dtos; generally use dto0 for hdmi */
	/* Express [24MHz / target pixel clock] as an exact rational
	 * number (coefficient of two integer numbers.  DCCG_AUDIO_DTOx_PHASE
	 * is the numerator, DCCG_AUDIO_DTOx_MODULE is the denominator
	 */
	tmp = RREG32(mmDCCG_AUDIO_DTO_SOURCE);
	tmp = REG_SET_FIELD(tmp, DCCG_AUDIO_DTO_SOURCE, DCCG_AUDIO_DTO0_SOURCE_SEL,
			    amdgpu_crtc->crtc_id);
	WREG32(mmDCCG_AUDIO_DTO_SOURCE, tmp);
	WREG32(mmDCCG_AUDIO_DTO0_PHASE, dto_phase);
	WREG32(mmDCCG_AUDIO_DTO0_MODULE, dto_modulo);
}