#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int device; int revision; } ;
struct TYPE_8__ {int scheduler; } ;
struct TYPE_7__ {struct pci_dev* pdev; } ;
struct drm_i915_private {int num_fence_regs; TYPE_2__ caps; int /*<<< orphan*/  huc; int /*<<< orphan*/ * engine; int /*<<< orphan*/  overlay; TYPE_1__ drm; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_9__ {int param; int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ drm_i915_getparam_t ;
struct TYPE_10__ {int eu_total; int min_eu_in_pool; int slice_mask; int* subslice_mask; } ;
struct TYPE_12__ {int cs_timestamp_frequency_khz; TYPE_4__ sseu; } ;
struct TYPE_11__ {int /*<<< orphan*/  enable_hangcheck; } ;

/* Variables and functions */
 size_t BCS ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int HAS_LEGACY_SEMAPHORES (struct drm_i915_private*) ; 
 int HAS_LLC (struct drm_i915_private*) ; 
 int HAS_POOLED_EU (struct drm_i915_private*) ; 
 int HAS_RESOURCE_STREAMER (struct drm_i915_private*) ; 
 int HAS_WT (struct drm_i915_private*) ; 
#define  I915_PARAM_ALLOW_BATCHBUFFER 178 
#define  I915_PARAM_CHIPSET_ID 177 
#define  I915_PARAM_CMD_PARSER_VERSION 176 
#define  I915_PARAM_CS_TIMESTAMP_FREQUENCY 175 
#define  I915_PARAM_EU_TOTAL 174 
#define  I915_PARAM_HAS_ALIASING_PPGTT 173 
#define  I915_PARAM_HAS_BLT 172 
#define  I915_PARAM_HAS_BSD 171 
#define  I915_PARAM_HAS_BSD2 170 
#define  I915_PARAM_HAS_COHERENT_PHYS_GTT 169 
#define  I915_PARAM_HAS_COHERENT_RINGS 168 
#define  I915_PARAM_HAS_CONTEXT_ISOLATION 167 
#define  I915_PARAM_HAS_EXECBUF2 166 
#define  I915_PARAM_HAS_EXEC_ASYNC 165 
#define  I915_PARAM_HAS_EXEC_BATCH_FIRST 164 
#define  I915_PARAM_HAS_EXEC_CAPTURE 163 
#define  I915_PARAM_HAS_EXEC_CONSTANTS 162 
#define  I915_PARAM_HAS_EXEC_FENCE 161 
#define  I915_PARAM_HAS_EXEC_FENCE_ARRAY 160 
#define  I915_PARAM_HAS_EXEC_HANDLE_LUT 159 
#define  I915_PARAM_HAS_EXEC_NO_RELOC 158 
#define  I915_PARAM_HAS_EXEC_SOFTPIN 157 
#define  I915_PARAM_HAS_GEM 156 
#define  I915_PARAM_HAS_GEN7_SOL_RESET 155 
#define  I915_PARAM_HAS_GPU_RESET 154 
#define  I915_PARAM_HAS_LLC 153 
#define  I915_PARAM_HAS_OVERLAY 152 
#define  I915_PARAM_HAS_PAGEFLIPPING 151 
#define  I915_PARAM_HAS_PINNED_BATCHES 150 
#define  I915_PARAM_HAS_POOLED_EU 149 
#define  I915_PARAM_HAS_PRIME_VMAP_FLUSH 148 
#define  I915_PARAM_HAS_RELAXED_DELTA 147 
#define  I915_PARAM_HAS_RELAXED_FENCING 146 
#define  I915_PARAM_HAS_RESOURCE_STREAMER 145 
#define  I915_PARAM_HAS_SCHEDULER 144 
#define  I915_PARAM_HAS_SECURE_BATCHES 143 
#define  I915_PARAM_HAS_SEMAPHORES 142 
#define  I915_PARAM_HAS_VEBOX 141 
#define  I915_PARAM_HAS_WAIT_TIMEOUT 140 
#define  I915_PARAM_HAS_WT 139 
#define  I915_PARAM_HUC_STATUS 138 
#define  I915_PARAM_IRQ_ACTIVE 137 
#define  I915_PARAM_LAST_DISPATCH 136 
#define  I915_PARAM_MIN_EU_IN_POOL 135 
#define  I915_PARAM_MMAP_GTT_VERSION 134 
#define  I915_PARAM_MMAP_VERSION 133 
#define  I915_PARAM_NUM_FENCES_AVAIL 132 
#define  I915_PARAM_REVISION 131 
#define  I915_PARAM_SLICE_MASK 130 
#define  I915_PARAM_SUBSLICE_MASK 129 
#define  I915_PARAM_SUBSLICE_TOTAL 128 
 TYPE_6__* INTEL_INFO (struct drm_i915_private*) ; 
 int USES_PPGTT (struct drm_i915_private*) ; 
 size_t VCS ; 
 size_t VCS2 ; 
 size_t VECS ; 
 int capable (int /*<<< orphan*/ ) ; 
 int i915_cmd_parser_get_version (struct drm_i915_private*) ; 
 int i915_gem_mmap_gtt_version () ; 
 TYPE_5__ i915_modparams ; 
 int intel_engines_has_context_isolation (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_has_gpu_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_has_reset_engine (struct drm_i915_private*) ; 
 int intel_huc_check_status (int /*<<< orphan*/ *) ; 
 scalar_t__ put_user (int,int /*<<< orphan*/ ) ; 
 int sseu_subslice_total (TYPE_4__*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int i915_getparam_ioctl(struct drm_device *dev, void *data,
			       struct drm_file *file_priv)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct pci_dev *pdev = dev_priv->drm.pdev;
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
		value = pdev->device;
		break;
	case I915_PARAM_REVISION:
		value = pdev->revision;
		break;
	case I915_PARAM_NUM_FENCES_AVAIL:
		value = dev_priv->num_fence_regs;
		break;
	case I915_PARAM_HAS_OVERLAY:
		value = dev_priv->overlay ? 1 : 0;
		break;
	case I915_PARAM_HAS_BSD:
		value = !!dev_priv->engine[VCS];
		break;
	case I915_PARAM_HAS_BLT:
		value = !!dev_priv->engine[BCS];
		break;
	case I915_PARAM_HAS_VEBOX:
		value = !!dev_priv->engine[VECS];
		break;
	case I915_PARAM_HAS_BSD2:
		value = !!dev_priv->engine[VCS2];
		break;
	case I915_PARAM_HAS_LLC:
		value = HAS_LLC(dev_priv);
		break;
	case I915_PARAM_HAS_WT:
		value = HAS_WT(dev_priv);
		break;
	case I915_PARAM_HAS_ALIASING_PPGTT:
		value = USES_PPGTT(dev_priv);
		break;
	case I915_PARAM_HAS_SEMAPHORES:
		value = HAS_LEGACY_SEMAPHORES(dev_priv);
		break;
	case I915_PARAM_HAS_SECURE_BATCHES:
		value = capable(CAP_SYS_ADMIN);
		break;
	case I915_PARAM_CMD_PARSER_VERSION:
		value = i915_cmd_parser_get_version(dev_priv);
		break;
	case I915_PARAM_SUBSLICE_TOTAL:
		value = sseu_subslice_total(&INTEL_INFO(dev_priv)->sseu);
		if (!value)
			return -ENODEV;
		break;
	case I915_PARAM_EU_TOTAL:
		value = INTEL_INFO(dev_priv)->sseu.eu_total;
		if (!value)
			return -ENODEV;
		break;
	case I915_PARAM_HAS_GPU_RESET:
		value = i915_modparams.enable_hangcheck &&
			intel_has_gpu_reset(dev_priv);
		if (value && intel_has_reset_engine(dev_priv))
			value = 2;
		break;
	case I915_PARAM_HAS_RESOURCE_STREAMER:
		value = HAS_RESOURCE_STREAMER(dev_priv);
		break;
	case I915_PARAM_HAS_POOLED_EU:
		value = HAS_POOLED_EU(dev_priv);
		break;
	case I915_PARAM_MIN_EU_IN_POOL:
		value = INTEL_INFO(dev_priv)->sseu.min_eu_in_pool;
		break;
	case I915_PARAM_HUC_STATUS:
		value = intel_huc_check_status(&dev_priv->huc);
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
		value = dev_priv->caps.scheduler;
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
		/* For the time being all of these are always true;
		 * if some supported hardware does not have one of these
		 * features this value needs to be provided from
		 * INTEL_INFO(), a feature macro, or similar.
		 */
		value = 1;
		break;
	case I915_PARAM_HAS_CONTEXT_ISOLATION:
		value = intel_engines_has_context_isolation(dev_priv);
		break;
	case I915_PARAM_SLICE_MASK:
		value = INTEL_INFO(dev_priv)->sseu.slice_mask;
		if (!value)
			return -ENODEV;
		break;
	case I915_PARAM_SUBSLICE_MASK:
		value = INTEL_INFO(dev_priv)->sseu.subslice_mask[0];
		if (!value)
			return -ENODEV;
		break;
	case I915_PARAM_CS_TIMESTAMP_FREQUENCY:
		value = 1000 * INTEL_INFO(dev_priv)->cs_timestamp_frequency_khz;
		break;
	default:
		DRM_DEBUG("Unknown parameter %d\n", param->param);
		return -EINVAL;
	}

	if (put_user(value, param->value))
		return -EFAULT;

	return 0;
}