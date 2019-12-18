#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_60__   TYPE_9__ ;
typedef  struct TYPE_59__   TYPE_8__ ;
typedef  struct TYPE_58__   TYPE_7__ ;
typedef  struct TYPE_57__   TYPE_6__ ;
typedef  struct TYPE_56__   TYPE_5__ ;
typedef  struct TYPE_55__   TYPE_4__ ;
typedef  struct TYPE_54__   TYPE_3__ ;
typedef  struct TYPE_53__   TYPE_30__ ;
typedef  struct TYPE_52__   TYPE_2__ ;
typedef  struct TYPE_51__   TYPE_29__ ;
typedef  struct TYPE_50__   TYPE_28__ ;
typedef  struct TYPE_49__   TYPE_27__ ;
typedef  struct TYPE_48__   TYPE_26__ ;
typedef  struct TYPE_47__   TYPE_25__ ;
typedef  struct TYPE_46__   TYPE_24__ ;
typedef  struct TYPE_45__   TYPE_23__ ;
typedef  struct TYPE_44__   TYPE_22__ ;
typedef  struct TYPE_43__   TYPE_21__ ;
typedef  struct TYPE_42__   TYPE_20__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_19__ ;
typedef  struct TYPE_39__   TYPE_18__ ;
typedef  struct TYPE_38__   TYPE_17__ ;
typedef  struct TYPE_37__   TYPE_16__ ;
typedef  struct TYPE_36__   TYPE_15__ ;
typedef  struct TYPE_35__   TYPE_14__ ;
typedef  struct TYPE_34__   TYPE_13__ ;
typedef  struct TYPE_33__   TYPE_12__ ;
typedef  struct TYPE_32__   TYPE_11__ ;
typedef  struct TYPE_31__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct drm_amdgpu_info_hw_ip {int available_rings; void* ib_size_alignment; void* ib_start_alignment; scalar_t__ capabilities_flags; int /*<<< orphan*/  hw_ip_version_minor; int /*<<< orphan*/  hw_ip_version_major; } ;
struct TYPE_55__ {scalar_t__ ip_instance; int type; } ;
struct drm_amdgpu_info {TYPE_4__ query_hw_ip; } ;
struct TYPE_53__ {unsigned int num_vcn_inst; unsigned int num_enc_rings; TYPE_29__* inst; } ;
struct TYPE_48__ {unsigned int num_uvd_inst; int harvest_config; unsigned int num_enc_rings; TYPE_21__* inst; } ;
struct TYPE_39__ {unsigned int num_rings; TYPE_17__* ring; } ;
struct TYPE_34__ {unsigned int num_instances; TYPE_12__* instance; } ;
struct TYPE_60__ {unsigned int num_gfx_rings; unsigned int num_compute_rings; TYPE_8__* compute_ring; TYPE_6__* gfx_ring; } ;
struct amdgpu_device {unsigned int num_ip_blocks; TYPE_3__* ip_blocks; TYPE_30__ vcn; TYPE_26__ uvd; TYPE_18__ vce; TYPE_13__ sdma; TYPE_9__ gfx; } ;
typedef  enum amd_ip_block_type { ____Placeholder_amd_ip_block_type } amd_ip_block_type ;
struct TYPE_58__ {int /*<<< orphan*/  ready; } ;
struct TYPE_59__ {TYPE_7__ sched; } ;
struct TYPE_56__ {int /*<<< orphan*/  ready; } ;
struct TYPE_57__ {TYPE_5__ sched; } ;
struct TYPE_41__ {scalar_t__ valid; } ;
struct TYPE_54__ {TYPE_2__* version; TYPE_1__ status; } ;
struct TYPE_52__ {int type; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_49__ {int /*<<< orphan*/  ready; } ;
struct TYPE_50__ {TYPE_27__ sched; } ;
struct TYPE_44__ {int /*<<< orphan*/  ready; } ;
struct TYPE_45__ {TYPE_22__ sched; } ;
struct TYPE_51__ {TYPE_28__ ring_jpeg; TYPE_25__* ring_enc; TYPE_23__ ring_dec; } ;
struct TYPE_46__ {int /*<<< orphan*/  ready; } ;
struct TYPE_47__ {TYPE_24__ sched; } ;
struct TYPE_35__ {int /*<<< orphan*/  ready; } ;
struct TYPE_36__ {TYPE_14__ sched; } ;
struct TYPE_43__ {TYPE_20__* ring_enc; TYPE_15__ ring; } ;
struct TYPE_40__ {int /*<<< orphan*/  ready; } ;
struct TYPE_42__ {TYPE_19__ sched; } ;
struct TYPE_37__ {int /*<<< orphan*/  ready; } ;
struct TYPE_38__ {TYPE_16__ sched; } ;
struct TYPE_31__ {int /*<<< orphan*/  ready; } ;
struct TYPE_32__ {TYPE_10__ sched; } ;
struct TYPE_33__ {TYPE_11__ ring; } ;

/* Variables and functions */
#define  AMDGPU_HW_IP_COMPUTE 136 
#define  AMDGPU_HW_IP_DMA 135 
#define  AMDGPU_HW_IP_GFX 134 
 scalar_t__ AMDGPU_HW_IP_INSTANCE_MAX_COUNT ; 
#define  AMDGPU_HW_IP_UVD 133 
#define  AMDGPU_HW_IP_UVD_ENC 132 
#define  AMDGPU_HW_IP_VCE 131 
#define  AMDGPU_HW_IP_VCN_DEC 130 
#define  AMDGPU_HW_IP_VCN_ENC 129 
#define  AMDGPU_HW_IP_VCN_JPEG 128 
 int AMD_IP_BLOCK_TYPE_GFX ; 
 int AMD_IP_BLOCK_TYPE_SDMA ; 
 int AMD_IP_BLOCK_TYPE_UVD ; 
 int AMD_IP_BLOCK_TYPE_VCE ; 
 int AMD_IP_BLOCK_TYPE_VCN ; 
 int EINVAL ; 
 int /*<<< orphan*/ * amdgpu_ctx_num_entities ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int amdgpu_hw_ip_info(struct amdgpu_device *adev,
			     struct drm_amdgpu_info *info,
			     struct drm_amdgpu_info_hw_ip *result)
{
	uint32_t ib_start_alignment = 0;
	uint32_t ib_size_alignment = 0;
	enum amd_ip_block_type type;
	unsigned int num_rings = 0;
	unsigned int i, j;

	if (info->query_hw_ip.ip_instance >= AMDGPU_HW_IP_INSTANCE_MAX_COUNT)
		return -EINVAL;

	switch (info->query_hw_ip.type) {
	case AMDGPU_HW_IP_GFX:
		type = AMD_IP_BLOCK_TYPE_GFX;
		for (i = 0; i < adev->gfx.num_gfx_rings; i++)
			if (adev->gfx.gfx_ring[i].sched.ready)
				++num_rings;
		ib_start_alignment = 32;
		ib_size_alignment = 32;
		break;
	case AMDGPU_HW_IP_COMPUTE:
		type = AMD_IP_BLOCK_TYPE_GFX;
		for (i = 0; i < adev->gfx.num_compute_rings; i++)
			if (adev->gfx.compute_ring[i].sched.ready)
				++num_rings;
		ib_start_alignment = 32;
		ib_size_alignment = 32;
		break;
	case AMDGPU_HW_IP_DMA:
		type = AMD_IP_BLOCK_TYPE_SDMA;
		for (i = 0; i < adev->sdma.num_instances; i++)
			if (adev->sdma.instance[i].ring.sched.ready)
				++num_rings;
		ib_start_alignment = 256;
		ib_size_alignment = 4;
		break;
	case AMDGPU_HW_IP_UVD:
		type = AMD_IP_BLOCK_TYPE_UVD;
		for (i = 0; i < adev->uvd.num_uvd_inst; i++) {
			if (adev->uvd.harvest_config & (1 << i))
				continue;

			if (adev->uvd.inst[i].ring.sched.ready)
				++num_rings;
		}
		ib_start_alignment = 64;
		ib_size_alignment = 64;
		break;
	case AMDGPU_HW_IP_VCE:
		type = AMD_IP_BLOCK_TYPE_VCE;
		for (i = 0; i < adev->vce.num_rings; i++)
			if (adev->vce.ring[i].sched.ready)
				++num_rings;
		ib_start_alignment = 4;
		ib_size_alignment = 1;
		break;
	case AMDGPU_HW_IP_UVD_ENC:
		type = AMD_IP_BLOCK_TYPE_UVD;
		for (i = 0; i < adev->uvd.num_uvd_inst; i++) {
			if (adev->uvd.harvest_config & (1 << i))
				continue;

			for (j = 0; j < adev->uvd.num_enc_rings; j++)
				if (adev->uvd.inst[i].ring_enc[j].sched.ready)
					++num_rings;
		}
		ib_start_alignment = 64;
		ib_size_alignment = 64;
		break;
	case AMDGPU_HW_IP_VCN_DEC:
		type = AMD_IP_BLOCK_TYPE_VCN;
		for (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			if (adev->uvd.harvest_config & (1 << i))
				continue;

			if (adev->vcn.inst[i].ring_dec.sched.ready)
				++num_rings;
		}
		ib_start_alignment = 16;
		ib_size_alignment = 16;
		break;
	case AMDGPU_HW_IP_VCN_ENC:
		type = AMD_IP_BLOCK_TYPE_VCN;
		for (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			if (adev->uvd.harvest_config & (1 << i))
				continue;

			for (j = 0; j < adev->vcn.num_enc_rings; j++)
				if (adev->vcn.inst[i].ring_enc[j].sched.ready)
					++num_rings;
		}
		ib_start_alignment = 64;
		ib_size_alignment = 1;
		break;
	case AMDGPU_HW_IP_VCN_JPEG:
		type = AMD_IP_BLOCK_TYPE_VCN;
		for (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			if (adev->uvd.harvest_config & (1 << i))
				continue;

			if (adev->vcn.inst[i].ring_jpeg.sched.ready)
				++num_rings;
		}
		ib_start_alignment = 16;
		ib_size_alignment = 16;
		break;
	default:
		return -EINVAL;
	}

	for (i = 0; i < adev->num_ip_blocks; i++)
		if (adev->ip_blocks[i].version->type == type &&
		    adev->ip_blocks[i].status.valid)
			break;

	if (i == adev->num_ip_blocks)
		return 0;

	num_rings = min(amdgpu_ctx_num_entities[info->query_hw_ip.type],
			num_rings);

	result->hw_ip_version_major = adev->ip_blocks[i].version->major;
	result->hw_ip_version_minor = adev->ip_blocks[i].version->minor;
	result->capabilities_flags = 0;
	result->available_rings = (1 << num_rings) - 1;
	result->ib_start_alignment = ib_start_alignment;
	result->ib_size_alignment = ib_size_alignment;
	return 0;
}