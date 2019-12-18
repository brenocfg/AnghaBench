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
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct TYPE_5__ {unsigned long long model; unsigned long long revision; unsigned long long features; unsigned long long minor_features0; unsigned long long minor_features1; unsigned long long minor_features2; unsigned long long minor_features3; unsigned long long minor_features4; unsigned long long minor_features5; unsigned long long minor_features6; unsigned long long minor_features7; unsigned long long minor_features8; unsigned long long minor_features9; unsigned long long minor_features10; unsigned long long minor_features11; unsigned long long stream_count; unsigned long long register_max; unsigned long long thread_count; unsigned long long vertex_cache_size; unsigned long long shader_core_count; unsigned long long pixel_pipes; unsigned long long vertex_output_buffer_size; unsigned long long buffer_size; unsigned long long instruction_count; unsigned long long num_constants; unsigned long long varyings_count; } ;
struct etnaviv_gpu {int /*<<< orphan*/  dev; TYPE_2__ identity; TYPE_1__* drm; } ;
struct etnaviv_drm_private {TYPE_3__* mmu_global; } ;
struct TYPE_6__ {int /*<<< orphan*/  version; } ;
struct TYPE_4__ {struct etnaviv_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETNAVIV_IOMMU_V2 ; 
#define  ETNAVIV_PARAM_GPU_BUFFER_SIZE 154 
#define  ETNAVIV_PARAM_GPU_FEATURES_0 153 
#define  ETNAVIV_PARAM_GPU_FEATURES_1 152 
#define  ETNAVIV_PARAM_GPU_FEATURES_10 151 
#define  ETNAVIV_PARAM_GPU_FEATURES_11 150 
#define  ETNAVIV_PARAM_GPU_FEATURES_12 149 
#define  ETNAVIV_PARAM_GPU_FEATURES_2 148 
#define  ETNAVIV_PARAM_GPU_FEATURES_3 147 
#define  ETNAVIV_PARAM_GPU_FEATURES_4 146 
#define  ETNAVIV_PARAM_GPU_FEATURES_5 145 
#define  ETNAVIV_PARAM_GPU_FEATURES_6 144 
#define  ETNAVIV_PARAM_GPU_FEATURES_7 143 
#define  ETNAVIV_PARAM_GPU_FEATURES_8 142 
#define  ETNAVIV_PARAM_GPU_FEATURES_9 141 
#define  ETNAVIV_PARAM_GPU_INSTRUCTION_COUNT 140 
#define  ETNAVIV_PARAM_GPU_MODEL 139 
#define  ETNAVIV_PARAM_GPU_NUM_CONSTANTS 138 
#define  ETNAVIV_PARAM_GPU_NUM_VARYINGS 137 
#define  ETNAVIV_PARAM_GPU_PIXEL_PIPES 136 
#define  ETNAVIV_PARAM_GPU_REGISTER_MAX 135 
#define  ETNAVIV_PARAM_GPU_REVISION 134 
#define  ETNAVIV_PARAM_GPU_SHADER_CORE_COUNT 133 
#define  ETNAVIV_PARAM_GPU_STREAM_COUNT 132 
#define  ETNAVIV_PARAM_GPU_THREAD_COUNT 131 
#define  ETNAVIV_PARAM_GPU_VERTEX_CACHE_SIZE 130 
#define  ETNAVIV_PARAM_GPU_VERTEX_OUTPUT_BUFFER_SIZE 129 
#define  ETNAVIV_PARAM_SOFTPIN_START_ADDR 128 
 unsigned long long ETNAVIV_SOFTPIN_START_ADDRESS ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 

int etnaviv_gpu_get_param(struct etnaviv_gpu *gpu, u32 param, u64 *value)
{
	struct etnaviv_drm_private *priv = gpu->drm->dev_private;

	switch (param) {
	case ETNAVIV_PARAM_GPU_MODEL:
		*value = gpu->identity.model;
		break;

	case ETNAVIV_PARAM_GPU_REVISION:
		*value = gpu->identity.revision;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_0:
		*value = gpu->identity.features;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_1:
		*value = gpu->identity.minor_features0;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_2:
		*value = gpu->identity.minor_features1;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_3:
		*value = gpu->identity.minor_features2;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_4:
		*value = gpu->identity.minor_features3;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_5:
		*value = gpu->identity.minor_features4;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_6:
		*value = gpu->identity.minor_features5;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_7:
		*value = gpu->identity.minor_features6;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_8:
		*value = gpu->identity.minor_features7;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_9:
		*value = gpu->identity.minor_features8;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_10:
		*value = gpu->identity.minor_features9;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_11:
		*value = gpu->identity.minor_features10;
		break;

	case ETNAVIV_PARAM_GPU_FEATURES_12:
		*value = gpu->identity.minor_features11;
		break;

	case ETNAVIV_PARAM_GPU_STREAM_COUNT:
		*value = gpu->identity.stream_count;
		break;

	case ETNAVIV_PARAM_GPU_REGISTER_MAX:
		*value = gpu->identity.register_max;
		break;

	case ETNAVIV_PARAM_GPU_THREAD_COUNT:
		*value = gpu->identity.thread_count;
		break;

	case ETNAVIV_PARAM_GPU_VERTEX_CACHE_SIZE:
		*value = gpu->identity.vertex_cache_size;
		break;

	case ETNAVIV_PARAM_GPU_SHADER_CORE_COUNT:
		*value = gpu->identity.shader_core_count;
		break;

	case ETNAVIV_PARAM_GPU_PIXEL_PIPES:
		*value = gpu->identity.pixel_pipes;
		break;

	case ETNAVIV_PARAM_GPU_VERTEX_OUTPUT_BUFFER_SIZE:
		*value = gpu->identity.vertex_output_buffer_size;
		break;

	case ETNAVIV_PARAM_GPU_BUFFER_SIZE:
		*value = gpu->identity.buffer_size;
		break;

	case ETNAVIV_PARAM_GPU_INSTRUCTION_COUNT:
		*value = gpu->identity.instruction_count;
		break;

	case ETNAVIV_PARAM_GPU_NUM_CONSTANTS:
		*value = gpu->identity.num_constants;
		break;

	case ETNAVIV_PARAM_GPU_NUM_VARYINGS:
		*value = gpu->identity.varyings_count;
		break;

	case ETNAVIV_PARAM_SOFTPIN_START_ADDR:
		if (priv->mmu_global->version == ETNAVIV_IOMMU_V2)
			*value = ETNAVIV_SOFTPIN_START_ADDRESS;
		else
			*value = ~0ULL;
		break;

	default:
		DBG("%s: invalid param: %u", dev_name(gpu->dev), param);
		return -EINVAL;
	}

	return 0;
}