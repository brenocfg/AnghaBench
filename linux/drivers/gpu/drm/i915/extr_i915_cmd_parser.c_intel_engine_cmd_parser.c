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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct intel_engine_cs {int dummy; } ;
struct i915_gem_context {int jump_whitelist_cmds; int /*<<< orphan*/  jump_whitelist; } ;
struct TYPE_6__ {int /*<<< orphan*/  mapping; } ;
struct drm_i915_gem_object {TYPE_3__ mm; } ;
struct TYPE_5__ {scalar_t__ value; } ;
struct TYPE_4__ {int fixed; int mask; } ;
struct drm_i915_cmd_descriptor {int flags; TYPE_2__ cmd; TYPE_1__ length; } ;

/* Variables and functions */
 int CMD_DESC_FIXED ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int EACCES ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (int*) ; 
 int LENGTH_BIAS ; 
 int MI_BATCH_BUFFER_END ; 
 scalar_t__ MI_BATCH_BUFFER_START ; 
 int PTR_ERR (int*) ; 
 int check_bbstart (struct i915_gem_context*,int*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_cmd (struct intel_engine_cs*,struct drm_i915_cmd_descriptor const*,int*,int) ; 
 int* copy_batch (struct drm_i915_gem_object*,struct drm_i915_gem_object*,int,int,int*) ; 
 int /*<<< orphan*/  drm_clflush_virt_range (void*,int) ; 
 struct drm_i915_cmd_descriptor* find_cmd (struct intel_engine_cs*,int,struct drm_i915_cmd_descriptor const*,struct drm_i915_cmd_descriptor*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  init_whitelist (struct i915_gem_context*,int) ; 
 struct drm_i915_cmd_descriptor noop_desc ; 
 void* page_mask_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

int intel_engine_cmd_parser(struct i915_gem_context *ctx,
			    struct intel_engine_cs *engine,
			    struct drm_i915_gem_object *batch_obj,
			    u64 batch_start,
			    u32 batch_start_offset,
			    u32 batch_len,
			    struct drm_i915_gem_object *shadow_batch_obj,
			    u64 shadow_batch_start)
{
	u32 *cmd, *batch_end, offset = 0;
	struct drm_i915_cmd_descriptor default_desc = noop_desc;
	const struct drm_i915_cmd_descriptor *desc = &default_desc;
	bool needs_clflush_after = false;
	int ret = 0;

	cmd = copy_batch(shadow_batch_obj, batch_obj,
			 batch_start_offset, batch_len,
			 &needs_clflush_after);
	if (IS_ERR(cmd)) {
		DRM_DEBUG_DRIVER("CMD: Failed to copy batch\n");
		return PTR_ERR(cmd);
	}

	init_whitelist(ctx, batch_len);

	/*
	 * We use the batch length as size because the shadow object is as
	 * large or larger and copy_batch() will write MI_NOPs to the extra
	 * space. Parsing should be faster in some cases this way.
	 */
	batch_end = cmd + (batch_len / sizeof(*batch_end));
	do {
		u32 length;

		if (*cmd == MI_BATCH_BUFFER_END)
			break;

		desc = find_cmd(engine, *cmd, desc, &default_desc);
		if (!desc) {
			DRM_DEBUG_DRIVER("CMD: Unrecognized command: 0x%08X\n",
					 *cmd);
			ret = -EINVAL;
			goto err;
		}

		if (desc->flags & CMD_DESC_FIXED)
			length = desc->length.fixed;
		else
			length = ((*cmd & desc->length.mask) + LENGTH_BIAS);

		if ((batch_end - cmd) < length) {
			DRM_DEBUG_DRIVER("CMD: Command length exceeds batch length: 0x%08X length=%u batchlen=%td\n",
					 *cmd,
					 length,
					 batch_end - cmd);
			ret = -EINVAL;
			goto err;
		}

		if (!check_cmd(engine, desc, cmd, length)) {
			ret = -EACCES;
			goto err;
		}

		if (desc->cmd.value == MI_BATCH_BUFFER_START) {
			ret = check_bbstart(ctx, cmd, offset, length,
					    batch_len, batch_start,
					    shadow_batch_start);

			if (ret)
				goto err;
			break;
		}

		if (ctx->jump_whitelist_cmds > offset)
			set_bit(offset, ctx->jump_whitelist);

		cmd += length;
		offset += length;
		if  (cmd >= batch_end) {
			DRM_DEBUG_DRIVER("CMD: Got to the end of the buffer w/o a BBE cmd!\n");
			ret = -EINVAL;
			goto err;
		}
	} while (1);

	if (needs_clflush_after) {
		void *ptr = page_mask_bits(shadow_batch_obj->mm.mapping);

		drm_clflush_virt_range(ptr, (void *)(cmd + 1) - ptr);
	}

err:
	i915_gem_object_unpin_map(shadow_batch_obj);
	return ret;
}