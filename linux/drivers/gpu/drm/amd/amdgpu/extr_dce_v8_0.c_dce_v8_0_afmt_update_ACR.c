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
typedef  scalar_t__ uint32_t ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_encoder_atom_dig {TYPE_1__* afmt; } ;
struct amdgpu_encoder {struct amdgpu_encoder_atom_dig* enc_priv; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_afmt_acr {int cts_32khz; int n_32khz; int cts_44_1khz; int n_44_1khz; int cts_48khz; int n_48khz; } ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 int HDMI_ACR_32_0__HDMI_ACR_CTS_32__SHIFT ; 
 int HDMI_ACR_44_0__HDMI_ACR_CTS_44__SHIFT ; 
 int HDMI_ACR_48_0__HDMI_ACR_CTS_48__SHIFT ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 struct amdgpu_afmt_acr amdgpu_afmt_acr (scalar_t__) ; 
 scalar_t__ mmHDMI_ACR_32_0 ; 
 scalar_t__ mmHDMI_ACR_32_1 ; 
 scalar_t__ mmHDMI_ACR_44_0 ; 
 scalar_t__ mmHDMI_ACR_44_1 ; 
 scalar_t__ mmHDMI_ACR_48_0 ; 
 scalar_t__ mmHDMI_ACR_48_1 ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void dce_v8_0_afmt_update_ACR(struct drm_encoder *encoder, uint32_t clock)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_afmt_acr acr = amdgpu_afmt_acr(clock);
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	uint32_t offset = dig->afmt->offset;

	WREG32(mmHDMI_ACR_32_0 + offset, (acr.cts_32khz << HDMI_ACR_32_0__HDMI_ACR_CTS_32__SHIFT));
	WREG32(mmHDMI_ACR_32_1 + offset, acr.n_32khz);

	WREG32(mmHDMI_ACR_44_0 + offset, (acr.cts_44_1khz << HDMI_ACR_44_0__HDMI_ACR_CTS_44__SHIFT));
	WREG32(mmHDMI_ACR_44_1 + offset, acr.n_44_1khz);

	WREG32(mmHDMI_ACR_48_0 + offset, (acr.cts_48khz << HDMI_ACR_48_0__HDMI_ACR_CTS_48__SHIFT));
	WREG32(mmHDMI_ACR_48_1 + offset, acr.n_48khz);
}