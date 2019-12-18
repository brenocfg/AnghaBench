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
typedef  int u64 ;
typedef  int u32 ;
struct i915_gem_context {int jump_whitelist_cmds; int /*<<< orphan*/  jump_whitelist; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 scalar_t__ CMDPARSER_USES_GGTT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int EACCES ; 
 int EINVAL ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_bbstart(const struct i915_gem_context *ctx,
			 u32 *cmd, u32 offset, u32 length,
			 u32 batch_len,
			 u64 batch_start,
			 u64 shadow_batch_start)
{
	u64 jump_offset, jump_target;
	u32 target_cmd_offset, target_cmd_index;

	/* For igt compatibility on older platforms */
	if (CMDPARSER_USES_GGTT(ctx->i915)) {
		DRM_DEBUG("CMD: Rejecting BB_START for ggtt based submission\n");
		return -EACCES;
	}

	if (length != 3) {
		DRM_DEBUG("CMD: Recursive BB_START with bad length(%u)\n",
			  length);
		return -EINVAL;
	}

	jump_target = *(u64*)(cmd+1);
	jump_offset = jump_target - batch_start;

	/*
	 * Any underflow of jump_target is guaranteed to be outside the range
	 * of a u32, so >= test catches both too large and too small
	 */
	if (jump_offset >= batch_len) {
		DRM_DEBUG("CMD: BB_START to 0x%llx jumps out of BB\n",
			  jump_target);
		return -EINVAL;
	}

	/*
	 * This cannot overflow a u32 because we already checked jump_offset
	 * is within the BB, and the batch_len is a u32
	 */
	target_cmd_offset = lower_32_bits(jump_offset);
	target_cmd_index = target_cmd_offset / sizeof(u32);

	*(u64*)(cmd + 1) = shadow_batch_start + target_cmd_offset;

	if (target_cmd_index == offset)
		return 0;

	if (ctx->jump_whitelist_cmds <= target_cmd_index) {
		DRM_DEBUG("CMD: Rejecting BB_START - truncated whitelist array\n");
		return -EINVAL;
	} else if (!test_bit(target_cmd_index, ctx->jump_whitelist)) {
		DRM_DEBUG("CMD: BB_START to 0x%llx not a previously executed cmd\n",
			  jump_target);
		return -EINVAL;
	}

	return 0;
}