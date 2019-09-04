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
struct drm_i915_error_state_buf {int /*<<< orphan*/  i915; } ;
struct drm_i915_error_buffer {int engine; int /*<<< orphan*/  fence_reg; int /*<<< orphan*/  name; int /*<<< orphan*/  cache_level; scalar_t__ userptr; int /*<<< orphan*/  purgeable; int /*<<< orphan*/  dirty; int /*<<< orphan*/  tiling; int /*<<< orphan*/  wseqno; int /*<<< orphan*/  write_domain; int /*<<< orphan*/  read_domains; int /*<<< orphan*/  size; int /*<<< orphan*/  gtt_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_FENCE_REG_NONE ; 
 char* dirty_flag (int /*<<< orphan*/ ) ; 
 char* engine_name (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err_printf (struct drm_i915_error_state_buf*,char*,char const*,...) ; 
 int /*<<< orphan*/  err_puts (struct drm_i915_error_state_buf*,char*) ; 
 char* i915_cache_level_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 char* purgeable_flag (int /*<<< orphan*/ ) ; 
 char* tiling_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_error_buffers(struct drm_i915_error_state_buf *m,
				const char *name,
				struct drm_i915_error_buffer *err,
				int count)
{
	err_printf(m, "%s [%d]:\n", name, count);

	while (count--) {
		err_printf(m, "    %08x_%08x %8u %02x %02x %02x",
			   upper_32_bits(err->gtt_offset),
			   lower_32_bits(err->gtt_offset),
			   err->size,
			   err->read_domains,
			   err->write_domain,
			   err->wseqno);
		err_puts(m, tiling_flag(err->tiling));
		err_puts(m, dirty_flag(err->dirty));
		err_puts(m, purgeable_flag(err->purgeable));
		err_puts(m, err->userptr ? " userptr" : "");
		err_puts(m, err->engine != -1 ? " " : "");
		err_puts(m, engine_name(m->i915, err->engine));
		err_puts(m, i915_cache_level_str(m->i915, err->cache_level));

		if (err->name)
			err_printf(m, " (name: %d)", err->name);
		if (err->fence_reg != I915_FENCE_REG_NONE)
			err_printf(m, " (fence: %d)", err->fence_reg);

		err_puts(m, "\n");
		err++;
	}
}