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
typedef  int u16 ;
struct drm_encoder {int dummy; } ;
struct amdgpu_encoder {int encoder_id; } ;

/* Variables and functions */
 int ENCODER_OBJECT_ID_NONE ; 
#define  ENCODER_OBJECT_ID_NUTMEG 129 
#define  ENCODER_OBJECT_ID_TRAVIS 128 
 struct drm_encoder* amdgpu_get_external_encoder (struct drm_encoder*) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

u16 amdgpu_encoder_get_dp_bridge_encoder_id(struct drm_encoder *encoder)
{
	struct drm_encoder *other_encoder = amdgpu_get_external_encoder(encoder);

	if (other_encoder) {
		struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(other_encoder);

		switch (amdgpu_encoder->encoder_id) {
		case ENCODER_OBJECT_ID_TRAVIS:
		case ENCODER_OBJECT_ID_NUTMEG:
			return amdgpu_encoder->encoder_id;
		default:
			return ENCODER_OBJECT_ID_NONE;
		}
	}
	return ENCODER_OBJECT_ID_NONE;
}