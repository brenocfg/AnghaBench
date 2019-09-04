#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct amdgpu_ring {int dummy; } ;
struct amdgpu_queue_mgr {struct amdgpu_queue_mapper* mapper; } ;
struct amdgpu_queue_mapper {int hw_ip; int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {int num_enc_rings; } ;
struct TYPE_9__ {int num_uvd_inst; int harvest_config; int num_enc_rings; } ;
struct TYPE_8__ {int num_rings; } ;
struct TYPE_7__ {int num_instances; } ;
struct TYPE_6__ {int num_gfx_rings; int num_compute_rings; } ;
struct amdgpu_device {TYPE_5__ vcn; TYPE_4__ uvd; TYPE_3__ vce; TYPE_2__ sdma; TYPE_1__ gfx; } ;

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
 size_t AMDGPU_MAX_IP_NUM ; 
 size_t AMDGPU_MAX_RINGS ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,size_t,...) ; 
 int EINVAL ; 
 struct amdgpu_ring* amdgpu_get_cached_map (struct amdgpu_queue_mapper*,size_t) ; 
 int amdgpu_identity_map (struct amdgpu_device*,struct amdgpu_queue_mapper*,size_t,struct amdgpu_ring**) ; 
 int amdgpu_lru_map (struct amdgpu_device*,struct amdgpu_queue_mapper*,size_t,int,struct amdgpu_ring**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int amdgpu_queue_mgr_map(struct amdgpu_device *adev,
			 struct amdgpu_queue_mgr *mgr,
			 u32 hw_ip, u32 instance, u32 ring,
			 struct amdgpu_ring **out_ring)
{
	int i, r, ip_num_rings = 0;
	struct amdgpu_queue_mapper *mapper = &mgr->mapper[hw_ip];

	if (!adev || !mgr || !out_ring)
		return -EINVAL;

	if (hw_ip >= AMDGPU_MAX_IP_NUM)
		return -EINVAL;

	if (ring >= AMDGPU_MAX_RINGS)
		return -EINVAL;

	/* Right now all IPs have only one instance - multiple rings. */
	if (instance != 0) {
		DRM_DEBUG("invalid ip instance: %d\n", instance);
		return -EINVAL;
	}

	switch (hw_ip) {
	case AMDGPU_HW_IP_GFX:
		ip_num_rings = adev->gfx.num_gfx_rings;
		break;
	case AMDGPU_HW_IP_COMPUTE:
		ip_num_rings = adev->gfx.num_compute_rings;
		break;
	case AMDGPU_HW_IP_DMA:
		ip_num_rings = adev->sdma.num_instances;
		break;
	case AMDGPU_HW_IP_UVD:
		for (i = 0; i < adev->uvd.num_uvd_inst; i++) {
			if (!(adev->uvd.harvest_config & (1 << i)))
				ip_num_rings++;
		}
		break;
	case AMDGPU_HW_IP_VCE:
		ip_num_rings = adev->vce.num_rings;
		break;
	case AMDGPU_HW_IP_UVD_ENC:
		for (i = 0; i < adev->uvd.num_uvd_inst; i++) {
			if (!(adev->uvd.harvest_config & (1 << i)))
				ip_num_rings++;
		}
		ip_num_rings =
			adev->uvd.num_enc_rings * ip_num_rings;
		break;
	case AMDGPU_HW_IP_VCN_DEC:
		ip_num_rings = 1;
		break;
	case AMDGPU_HW_IP_VCN_ENC:
		ip_num_rings = adev->vcn.num_enc_rings;
		break;
	case AMDGPU_HW_IP_VCN_JPEG:
		ip_num_rings = 1;
		break;
	default:
		DRM_DEBUG("unknown ip type: %d\n", hw_ip);
		return -EINVAL;
	}

	if (ring >= ip_num_rings) {
		DRM_DEBUG("Ring index:%d exceeds maximum:%d for ip:%d\n",
			  ring, ip_num_rings, hw_ip);
		return -EINVAL;
	}

	mutex_lock(&mapper->lock);

	*out_ring = amdgpu_get_cached_map(mapper, ring);
	if (*out_ring) {
		/* cache hit */
		r = 0;
		goto out_unlock;
	}

	switch (mapper->hw_ip) {
	case AMDGPU_HW_IP_GFX:
	case AMDGPU_HW_IP_UVD:
	case AMDGPU_HW_IP_VCE:
	case AMDGPU_HW_IP_UVD_ENC:
	case AMDGPU_HW_IP_VCN_DEC:
	case AMDGPU_HW_IP_VCN_ENC:
	case AMDGPU_HW_IP_VCN_JPEG:
		r = amdgpu_identity_map(adev, mapper, ring, out_ring);
		break;
	case AMDGPU_HW_IP_DMA:
		r = amdgpu_lru_map(adev, mapper, ring, false, out_ring);
		break;
	case AMDGPU_HW_IP_COMPUTE:
		r = amdgpu_lru_map(adev, mapper, ring, true, out_ring);
		break;
	default:
		*out_ring = NULL;
		r = -EINVAL;
		DRM_DEBUG("unknown HW IP type: %d\n", mapper->hw_ip);
	}

out_unlock:
	mutex_unlock(&mapper->lock);
	return r;
}