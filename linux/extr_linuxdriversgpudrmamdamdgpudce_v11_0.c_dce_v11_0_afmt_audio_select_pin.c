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
typedef  int /*<<< orphan*/  u32 ;
struct drm_encoder {TYPE_3__* dev; } ;
struct amdgpu_encoder_atom_dig {TYPE_2__* afmt; } ;
struct amdgpu_encoder {struct amdgpu_encoder_atom_dig* enc_priv; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_6__ {struct amdgpu_device* dev_private; } ;
struct TYPE_5__ {scalar_t__ offset; TYPE_1__* pin; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_AUDIO_SRC_CONTROL ; 
 int /*<<< orphan*/  AFMT_AUDIO_SRC_SELECT ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mmAFMT_AUDIO_SRC_CONTROL ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void dce_v11_0_afmt_audio_select_pin(struct drm_encoder *encoder)
{
	struct amdgpu_device *adev = encoder->dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	u32 tmp;

	if (!dig || !dig->afmt || !dig->afmt->pin)
		return;

	tmp = RREG32(mmAFMT_AUDIO_SRC_CONTROL + dig->afmt->offset);
	tmp = REG_SET_FIELD(tmp, AFMT_AUDIO_SRC_CONTROL, AFMT_AUDIO_SRC_SELECT, dig->afmt->pin->id);
	WREG32(mmAFMT_AUDIO_SRC_CONTROL + dig->afmt->offset, tmp);
}