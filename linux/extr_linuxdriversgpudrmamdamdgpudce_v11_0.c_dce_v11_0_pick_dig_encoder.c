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

__attribute__((used)) static int dce_v11_0_pick_dig_encoder(struct drm_encoder *encoder)
{
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;

	switch (amdgpu_encoder->encoder_id) {
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
		if (dig->linkb)
			return 1;
		else
			return 0;
		break;
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
		if (dig->linkb)
			return 3;
		else
			return 2;
		break;
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
		if (dig->linkb)
			return 5;
		else
			return 4;
		break;
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		return 6;
		break;
	default:
		DRM_ERROR("invalid encoder_id: 0x%x\n", amdgpu_encoder->encoder_id);
		return 0;
	}
}