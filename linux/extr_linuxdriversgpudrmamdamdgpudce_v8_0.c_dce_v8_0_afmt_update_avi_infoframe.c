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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_encoder_atom_dig {TYPE_1__* afmt; } ;
struct amdgpu_encoder {struct amdgpu_encoder_atom_dig* enc_priv; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__ mmAFMT_AVI_INFO0 ; 
 scalar_t__ mmAFMT_AVI_INFO1 ; 
 scalar_t__ mmAFMT_AVI_INFO2 ; 
 scalar_t__ mmAFMT_AVI_INFO3 ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void dce_v8_0_afmt_update_avi_infoframe(struct drm_encoder *encoder,
					       void *buffer, size_t size)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	uint32_t offset = dig->afmt->offset;
	uint8_t *frame = buffer + 3;
	uint8_t *header = buffer;

	WREG32(mmAFMT_AVI_INFO0 + offset,
		frame[0x0] | (frame[0x1] << 8) | (frame[0x2] << 16) | (frame[0x3] << 24));
	WREG32(mmAFMT_AVI_INFO1 + offset,
		frame[0x4] | (frame[0x5] << 8) | (frame[0x6] << 16) | (frame[0x7] << 24));
	WREG32(mmAFMT_AVI_INFO2 + offset,
		frame[0x8] | (frame[0x9] << 8) | (frame[0xA] << 16) | (frame[0xB] << 24));
	WREG32(mmAFMT_AVI_INFO3 + offset,
		frame[0xC] | (frame[0xD] << 8) | (header[1] << 24));
}