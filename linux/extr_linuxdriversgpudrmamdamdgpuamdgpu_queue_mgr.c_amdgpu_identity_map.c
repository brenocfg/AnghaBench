#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct amdgpu_ring {int dummy; } ;
struct amdgpu_queue_mapper {int hw_ip; } ;
struct TYPE_14__ {struct amdgpu_ring ring_jpeg; struct amdgpu_ring* ring_enc; struct amdgpu_ring ring_dec; } ;
struct TYPE_13__ {TYPE_5__* inst; } ;
struct TYPE_11__ {struct amdgpu_ring* ring; } ;
struct TYPE_10__ {TYPE_2__* instance; } ;
struct TYPE_8__ {struct amdgpu_ring* compute_ring; struct amdgpu_ring* gfx_ring; } ;
struct amdgpu_device {TYPE_7__ vcn; TYPE_6__ uvd; TYPE_4__ vce; TYPE_3__ sdma; TYPE_1__ gfx; } ;
struct TYPE_12__ {struct amdgpu_ring* ring_enc; struct amdgpu_ring ring; } ;
struct TYPE_9__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
#define  AMDGPU_HW_IP_COMPUTE 136 
#define  AMDGPU_HW_IP_DMA 135 
#define  AMDGPU_HW_IP_GFX 134 
#define  AMDGPU_HW_IP_UVD 133 
#define  AMDGPU_HW_IP_UVD_ENC 132 
#define  AMDGPU_HW_IP_VCE 131 
#define  AMDGPU_HW_IP_VCN_DEC 130 
#define  AMDGPU_HW_IP_VCN_ENC 129 
#define  AMDGPU_HW_IP_VCN_JPEG 128 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int amdgpu_update_cached_map (struct amdgpu_queue_mapper*,size_t,struct amdgpu_ring*) ; 

__attribute__((used)) static int amdgpu_identity_map(struct amdgpu_device *adev,
			       struct amdgpu_queue_mapper *mapper,
			       u32 ring,
			       struct amdgpu_ring **out_ring)
{
	switch (mapper->hw_ip) {
	case AMDGPU_HW_IP_GFX:
		*out_ring = &adev->gfx.gfx_ring[ring];
		break;
	case AMDGPU_HW_IP_COMPUTE:
		*out_ring = &adev->gfx.compute_ring[ring];
		break;
	case AMDGPU_HW_IP_DMA:
		*out_ring = &adev->sdma.instance[ring].ring;
		break;
	case AMDGPU_HW_IP_UVD:
		*out_ring = &adev->uvd.inst[0].ring;
		break;
	case AMDGPU_HW_IP_VCE:
		*out_ring = &adev->vce.ring[ring];
		break;
	case AMDGPU_HW_IP_UVD_ENC:
		*out_ring = &adev->uvd.inst[0].ring_enc[ring];
		break;
	case AMDGPU_HW_IP_VCN_DEC:
		*out_ring = &adev->vcn.ring_dec;
		break;
	case AMDGPU_HW_IP_VCN_ENC:
		*out_ring = &adev->vcn.ring_enc[ring];
		break;
	case AMDGPU_HW_IP_VCN_JPEG:
		*out_ring = &adev->vcn.ring_jpeg;
		break;
	default:
		*out_ring = NULL;
		DRM_ERROR("unknown HW IP type: %d\n", mapper->hw_ip);
		return -EINVAL;
	}

	return amdgpu_update_cached_map(mapper, ring, *out_ring);
}