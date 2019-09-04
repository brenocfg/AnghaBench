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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  varyings_count; int /*<<< orphan*/  num_constants; int /*<<< orphan*/  instruction_count; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  vertex_output_buffer_size; int /*<<< orphan*/  pixel_pipes; int /*<<< orphan*/  shader_core_count; int /*<<< orphan*/  vertex_cache_size; int /*<<< orphan*/  thread_count; int /*<<< orphan*/  register_max; int /*<<< orphan*/  stream_count; int /*<<< orphan*/  minor_features11; int /*<<< orphan*/  minor_features10; int /*<<< orphan*/  minor_features9; int /*<<< orphan*/  minor_features8; int /*<<< orphan*/  minor_features7; int /*<<< orphan*/  minor_features6; int /*<<< orphan*/  minor_features5; int /*<<< orphan*/  minor_features4; int /*<<< orphan*/  minor_features3; int /*<<< orphan*/  minor_features2; int /*<<< orphan*/  minor_features1; int /*<<< orphan*/  minor_features0; int /*<<< orphan*/  features; int /*<<< orphan*/  revision; int /*<<< orphan*/  model; } ;
struct etnaviv_gpu {int /*<<< orphan*/  dev; TYPE_1__ identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
#define  ETNAVIV_PARAM_GPU_BUFFER_SIZE 153 
#define  ETNAVIV_PARAM_GPU_FEATURES_0 152 
#define  ETNAVIV_PARAM_GPU_FEATURES_1 151 
#define  ETNAVIV_PARAM_GPU_FEATURES_10 150 
#define  ETNAVIV_PARAM_GPU_FEATURES_11 149 
#define  ETNAVIV_PARAM_GPU_FEATURES_12 148 
#define  ETNAVIV_PARAM_GPU_FEATURES_2 147 
#define  ETNAVIV_PARAM_GPU_FEATURES_3 146 
#define  ETNAVIV_PARAM_GPU_FEATURES_4 145 
#define  ETNAVIV_PARAM_GPU_FEATURES_5 144 
#define  ETNAVIV_PARAM_GPU_FEATURES_6 143 
#define  ETNAVIV_PARAM_GPU_FEATURES_7 142 
#define  ETNAVIV_PARAM_GPU_FEATURES_8 141 
#define  ETNAVIV_PARAM_GPU_FEATURES_9 140 
#define  ETNAVIV_PARAM_GPU_INSTRUCTION_COUNT 139 
#define  ETNAVIV_PARAM_GPU_MODEL 138 
#define  ETNAVIV_PARAM_GPU_NUM_CONSTANTS 137 
#define  ETNAVIV_PARAM_GPU_NUM_VARYINGS 136 
#define  ETNAVIV_PARAM_GPU_PIXEL_PIPES 135 
#define  ETNAVIV_PARAM_GPU_REGISTER_MAX 134 
#define  ETNAVIV_PARAM_GPU_REVISION 133 
#define  ETNAVIV_PARAM_GPU_SHADER_CORE_COUNT 132 
#define  ETNAVIV_PARAM_GPU_STREAM_COUNT 131 
#define  ETNAVIV_PARAM_GPU_THREAD_COUNT 130 
#define  ETNAVIV_PARAM_GPU_VERTEX_CACHE_SIZE 129 
#define  ETNAVIV_PARAM_GPU_VERTEX_OUTPUT_BUFFER_SIZE 128 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 

int etnaviv_gpu_get_param(struct etnaviv_gpu *gpu, u32 param, u64 *value)
{
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

	default:
		DBG("%s: invalid param: %u", dev_name(gpu->dev), param);
		return -EINVAL;
	}

	return 0;
}