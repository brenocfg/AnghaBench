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
struct amdgpu_encoder {int devices; struct amdgpu_encoder* enc_priv; } ;

/* Variables and functions */
 int ATOM_DEVICE_LCD_SUPPORT ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_fini_backlight (struct amdgpu_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_encoder*) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void dce_v10_0_encoder_destroy(struct drm_encoder *encoder)
{
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	if (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
		amdgpu_atombios_encoder_fini_backlight(amdgpu_encoder);
	kfree(amdgpu_encoder->enc_priv);
	drm_encoder_cleanup(encoder);
	kfree(amdgpu_encoder);
}