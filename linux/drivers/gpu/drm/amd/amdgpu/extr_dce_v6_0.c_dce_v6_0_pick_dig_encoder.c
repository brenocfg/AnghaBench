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
struct amdgpu_encoder_atom_dig {int /*<<< orphan*/  linkb; } ;
struct amdgpu_encoder {int encoder_id; struct amdgpu_encoder_atom_dig* enc_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY 131 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 130 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 129 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY3 128 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static int dce_v6_0_pick_dig_encoder(struct drm_encoder *encoder)
{
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;

	switch (amdgpu_encoder->encoder_id) {
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
		return dig->linkb ? 1 : 0;
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
		return dig->linkb ? 3 : 2;
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
		return dig->linkb ? 5 : 4;
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		return 6;
	default:
		DRM_ERROR("invalid encoder_id: 0x%x\n", amdgpu_encoder->encoder_id);
		return 0;
	}
}