#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct sseu_dev_info {int eu_total; int min_eu_in_pool; int slice_mask; int* subslice_mask; } ;
struct TYPE_17__ {int scheduler; } ;
struct TYPE_15__ {int /*<<< orphan*/  huc; } ;
struct TYPE_16__ {TYPE_4__ uc; } ;
struct TYPE_14__ {int num_fences; } ;
struct TYPE_13__ {TYPE_1__* pdev; } ;
struct drm_i915_private {TYPE_6__ caps; TYPE_5__ gt; int /*<<< orphan*/  overlay; TYPE_3__ ggtt; TYPE_2__ drm; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_18__ {int param; int /*<<< orphan*/  value; } ;
typedef  TYPE_7__ drm_i915_getparam_t ;
struct TYPE_20__ {int cs_timestamp_frequency_khz; struct sseu_dev_info sseu; } ;
struct TYPE_19__ {int /*<<< orphan*/  enable_hangcheck; } ;
struct TYPE_12__ {int device; int revision; } ;
struct TYPE_11__ {int has_coherent_ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int HAS_LLC (struct drm_i915_private*) ; 
 int HAS_POOLED_EU (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HAS_SECURE_BATCHES (struct drm_i915_private*) ; 
 int HAS_WT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_ENGINE_CLASS_COPY ; 
 int /*<<< orphan*/  I915_ENGINE_CLASS_VIDEO ; 
 int /*<<< orphan*/  I915_ENGINE_CLASS_VIDEO_ENHANCE ; 
#define  I915_PARAM_ALLOW_BATCHBUFFER 180 
#define  I915_PARAM_CHIPSET_ID 179 
#define  I915_PARAM_CMD_PARSER_VERSION 178 
#define  I915_PARAM_CS_TIMESTAMP_FREQUENCY 177 
#define  I915_PARAM_EU_TOTAL 176 
#define  I915_PARAM_HAS_ALIASING_PPGTT 175 
#define  I915_PARAM_HAS_BLT 174 
#define  I915_PARAM_HAS_BSD 173 
#define  I915_PARAM_HAS_BSD2 172 
#define  I915_PARAM_HAS_COHERENT_PHYS_GTT 171 
#define  I915_PARAM_HAS_COHERENT_RINGS 170 
#define  I915_PARAM_HAS_CONTEXT_ISOLATION 169 
#define  I915_PARAM_HAS_EXECBUF2 168 
#define  I915_PARAM_HAS_EXEC_ASYNC 167 
#define  I915_PARAM_HAS_EXEC_BATCH_FIRST 166 
#define  I915_PARAM_HAS_EXEC_CAPTURE 165 
#define  I915_PARAM_HAS_EXEC_CONSTANTS 164 
#define  I915_PARAM_HAS_EXEC_FENCE 163 
#define  I915_PARAM_HAS_EXEC_FENCE_ARRAY 162 
#define  I915_PARAM_HAS_EXEC_HANDLE_LUT 161 
#define  I915_PARAM_HAS_EXEC_NO_RELOC 160 
#define  I915_PARAM_HAS_EXEC_SOFTPIN 159 
#define  I915_PARAM_HAS_EXEC_SUBMIT_FENCE 158 
#define  I915_PARAM_HAS_GEM 157 
#define  I915_PARAM_HAS_GEN7_SOL_RESET 156 
#define  I915_PARAM_HAS_GPU_RESET 155 
#define  I915_PARAM_HAS_LLC 154 
#define  I915_PARAM_HAS_OVERLAY 153 
#define  I915_PARAM_HAS_PAGEFLIPPING 152 
#define  I915_PARAM_HAS_PINNED_BATCHES 151 
#define  I915_PARAM_HAS_POOLED_EU 150 
#define  I915_PARAM_HAS_PRIME_VMAP_FLUSH 149 
#define  I915_PARAM_HAS_RELAXED_DELTA 148 
#define  I915_PARAM_HAS_RELAXED_FENCING 147 
#define  I915_PARAM_HAS_RESOURCE_STREAMER 146 
#define  I915_PARAM_HAS_SCHEDULER 145 
#define  I915_PARAM_HAS_SECURE_BATCHES 144 
#define  I915_PARAM_HAS_SEMAPHORES 143 
#define  I915_PARAM_HAS_VEBOX 142 
#define  I915_PARAM_HAS_WAIT_TIMEOUT 141 
#define  I915_PARAM_HAS_WT 140 
#define  I915_PARAM_HUC_STATUS 139 
#define  I915_PARAM_IRQ_ACTIVE 138 
#define  I915_PARAM_LAST_DISPATCH 137 
#define  I915_PARAM_MIN_EU_IN_POOL 136 
#define  I915_PARAM_MMAP_GTT_COHERENT 135 
#define  I915_PARAM_MMAP_GTT_VERSION 134 
#define  I915_PARAM_MMAP_VERSION 133 
#define  I915_PARAM_NUM_FENCES_AVAIL 132 
#define  I915_PARAM_REVISION 131 
#define  I915_PARAM_SLICE_MASK 130 
#define  I915_PARAM_SUBSLICE_MASK 129 
#define  I915_PARAM_SUBSLICE_TOTAL 128 
 int I915_SCHEDULER_CAP_SEMAPHORES ; 
 TYPE_10__* INTEL_INFO (struct drm_i915_private*) ; 
 int INTEL_PPGTT (struct drm_i915_private*) ; 
 TYPE_9__* RUNTIME_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int i915_cmd_parser_get_version (struct drm_i915_private*) ; 
 int i915_gem_mmap_gtt_version () ; 
 TYPE_8__ i915_modparams ; 
 int /*<<< orphan*/  intel_engine_lookup_user (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int intel_engines_has_context_isolation (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_has_gpu_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_has_reset_engine (struct drm_i915_private*) ; 
 int intel_huc_check_status (int /*<<< orphan*/ *) ; 
 int intel_sseu_subslice_total (struct sseu_dev_info const*) ; 
 scalar_t__ put_user (int,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

int i915_getparam_ioctl(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	struct drm_i915_private *i915 = to_i915(dev);
	const struct sseu_dev_info *sseu = &RUNTIME_INFO(i915)->sseu;
	drm_i915_getparam_t *param = data;
	int value;

	switch (param->param) {
	case I915_PARAM_IRQ_ACTIVE:
	case I915_PARAM_ALLOW_BATCHBUFFER:
	case I915_PARAM_LAST_DISPATCH:
	case I915_PARAM_HAS_EXEC_CONSTANTS:
		/* Reject all old ums/dri params. */
		return -ENODEV;
	case I915_PARAM_CHIPSET_ID:
		value = i915->drm.pdev->device;
		break;
	case I915_PARAM_REVISION:
		value = i915->drm.pdev->revision;
		break;
	case I915_PARAM_NUM_FENCES_AVAIL:
		value = i915->ggtt.num_fences;
		break;
	case I915_PARAM_HAS_OVERLAY:
		value = !!i915->overlay;
		break;
	case I915_PARAM_HAS_BSD:
		value = !!intel_engine_lookup_user(i915,
						   I915_ENGINE_CLASS_VIDEO, 0);
		break;
	case I915_PARAM_HAS_BLT:
		value = !!intel_engine_lookup_user(i915,
						   I915_ENGINE_CLASS_COPY, 0);
		break;
	case I915_PARAM_HAS_VEBOX:
		value = !!intel_engine_lookup_user(i915,
						   I915_ENGINE_CLASS_VIDEO_ENHANCE, 0);
		break;
	case I915_PARAM_HAS_BSD2:
		value = !!intel_engine_lookup_user(i915,
						   I915_ENGINE_CLASS_VIDEO, 1);
		break;
	case I915_PARAM_HAS_LLC:
		value = HAS_LLC(i915);
		break;
	case I915_PARAM_HAS_WT:
		value = HAS_WT(i915);
		break;
	case I915_PARAM_HAS_ALIASING_PPGTT:
		value = INTEL_PPGTT(i915);
		break;
	case I915_PARAM_HAS_SEMAPHORES:
		value = !!(i915->caps.scheduler & I915_SCHEDULER_CAP_SEMAPHORES);
		break;
	case I915_PARAM_HAS_SECURE_BATCHES:
		value = HAS_SECURE_BATCHES(i915) && capable(CAP_SYS_ADMIN);
		break;
	case I915_PARAM_CMD_PARSER_VERSION:
		value = i915_cmd_parser_get_version(i915);
		break;
	case I915_PARAM_SUBSLICE_TOTAL:
		value = intel_sseu_subslice_total(sseu);
		if (!value)
			return -ENODEV;
		break;
	case I915_PARAM_EU_TOTAL:
		value = sseu->eu_total;
		if (!value)
			return -ENODEV;
		break;
	case I915_PARAM_HAS_GPU_RESET:
		value = i915_modparams.enable_hangcheck &&
			intel_has_gpu_reset(i915);
		if (value && intel_has_reset_engine(i915))
			value = 2;
		break;
	case I915_PARAM_HAS_RESOURCE_STREAMER:
		value = 0;
		break;
	case I915_PARAM_HAS_POOLED_EU:
		value = HAS_POOLED_EU(i915);
		break;
	case I915_PARAM_MIN_EU_IN_POOL:
		value = sseu->min_eu_in_pool;
		break;
	case I915_PARAM_HUC_STATUS:
		value = intel_huc_check_status(&i915->gt.uc.huc);
		if (value < 0)
			return value;
		break;
	case I915_PARAM_MMAP_GTT_VERSION:
		/* Though we've started our numbering from 1, and so class all
		 * earlier versions as 0, in effect their value is undefined as
		 * the ioctl will report EINVAL for the unknown param!
		 */
		value = i915_gem_mmap_gtt_version();
		break;
	case I915_PARAM_HAS_SCHEDULER:
		value = i915->caps.scheduler;
		break;

	case I915_PARAM_MMAP_VERSION:
		/* Remember to bump this if the version changes! */
	case I915_PARAM_HAS_GEM:
	case I915_PARAM_HAS_PAGEFLIPPING:
	case I915_PARAM_HAS_EXECBUF2: /* depends on GEM */
	case I915_PARAM_HAS_RELAXED_FENCING:
	case I915_PARAM_HAS_COHERENT_RINGS:
	case I915_PARAM_HAS_RELAXED_DELTA:
	case I915_PARAM_HAS_GEN7_SOL_RESET:
	case I915_PARAM_HAS_WAIT_TIMEOUT:
	case I915_PARAM_HAS_PRIME_VMAP_FLUSH:
	case I915_PARAM_HAS_PINNED_BATCHES:
	case I915_PARAM_HAS_EXEC_NO_RELOC:
	case I915_PARAM_HAS_EXEC_HANDLE_LUT:
	case I915_PARAM_HAS_COHERENT_PHYS_GTT:
	case I915_PARAM_HAS_EXEC_SOFTPIN:
	case I915_PARAM_HAS_EXEC_ASYNC:
	case I915_PARAM_HAS_EXEC_FENCE:
	case I915_PARAM_HAS_EXEC_CAPTURE:
	case I915_PARAM_HAS_EXEC_BATCH_FIRST:
	case I915_PARAM_HAS_EXEC_FENCE_ARRAY:
	case I915_PARAM_HAS_EXEC_SUBMIT_FENCE:
		/* For the time being all of these are always true;
		 * if some supported hardware does not have one of these
		 * features this value needs to be provided from
		 * INTEL_INFO(), a feature macro, or similar.
		 */
		value = 1;
		break;
	case I915_PARAM_HAS_CONTEXT_ISOLATION:
		value = intel_engines_has_context_isolation(i915);
		break;
	case I915_PARAM_SLICE_MASK:
		value = sseu->slice_mask;
		if (!value)
			return -ENODEV;
		break;
	case I915_PARAM_SUBSLICE_MASK:
		value = sseu->subslice_mask[0];
		if (!value)
			return -ENODEV;
		break;
	case I915_PARAM_CS_TIMESTAMP_FREQUENCY:
		value = 1000 * RUNTIME_INFO(i915)->cs_timestamp_frequency_khz;
		break;
	case I915_PARAM_MMAP_GTT_COHERENT:
		value = INTEL_INFO(i915)->has_coherent_ggtt;
		break;
	default:
		DRM_DEBUG("Unknown parameter %d\n", param->param);
		return -EINVAL;
	}

	if (put_user(value, param->value))
		return -EFAULT;

	return 0;
}