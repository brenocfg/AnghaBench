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
struct intel_engine_cs {int class; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; void* get_cmd_length_mask; void* reg_table_count; void* reg_tables; int /*<<< orphan*/  i915; } ;
struct drm_i915_cmd_table {int dummy; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
#define  COPY_ENGINE_CLASS 131 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_ENGINE_REQUIRES_CMD_PARSER ; 
 int /*<<< orphan*/  I915_ENGINE_USING_CMD_PARSER ; 
 scalar_t__ IS_GEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IS_HASWELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  RENDER_CLASS 130 
#define  VIDEO_DECODE_CLASS 129 
#define  VIDEO_ENHANCEMENT_CLASS 128 
 int /*<<< orphan*/  fini_hash_table (struct intel_engine_cs*) ; 
 void* gen7_blt_cmd_table ; 
 void* gen7_blt_get_cmd_length_mask ; 
 void* gen7_bsd_get_cmd_length_mask ; 
 void* gen7_render_cmd_table ; 
 void* gen7_render_get_cmd_length_mask ; 
 void* gen7_video_cmd_table ; 
 void* gen9_blt_cmd_table ; 
 void* gen9_blt_get_cmd_length_mask ; 
 void* gen9_blt_reg_tables ; 
 void* hsw_blt_reg_tables ; 
 void* hsw_blt_ring_cmd_table ; 
 void* hsw_render_reg_tables ; 
 void* hsw_render_ring_cmd_table ; 
 void* hsw_vebox_cmd_table ; 
 int init_hash_table (struct intel_engine_cs*,struct drm_i915_cmd_table const*,int) ; 
 void* ivb_blt_reg_tables ; 
 void* ivb_render_reg_tables ; 
 int /*<<< orphan*/  validate_cmds_sorted (struct intel_engine_cs*,struct drm_i915_cmd_table const*,int) ; 
 int /*<<< orphan*/  validate_regs_sorted (struct intel_engine_cs*) ; 

void intel_engine_init_cmd_parser(struct intel_engine_cs *engine)
{
	const struct drm_i915_cmd_table *cmd_tables;
	int cmd_table_count;
	int ret;

	if (!IS_GEN(engine->i915, 7) && !(IS_GEN(engine->i915, 9) &&
					  engine->class == COPY_ENGINE_CLASS))
		return;

	switch (engine->class) {
	case RENDER_CLASS:
		if (IS_HASWELL(engine->i915)) {
			cmd_tables = hsw_render_ring_cmd_table;
			cmd_table_count =
				ARRAY_SIZE(hsw_render_ring_cmd_table);
		} else {
			cmd_tables = gen7_render_cmd_table;
			cmd_table_count = ARRAY_SIZE(gen7_render_cmd_table);
		}

		if (IS_HASWELL(engine->i915)) {
			engine->reg_tables = hsw_render_reg_tables;
			engine->reg_table_count = ARRAY_SIZE(hsw_render_reg_tables);
		} else {
			engine->reg_tables = ivb_render_reg_tables;
			engine->reg_table_count = ARRAY_SIZE(ivb_render_reg_tables);
		}
		engine->get_cmd_length_mask = gen7_render_get_cmd_length_mask;
		break;
	case VIDEO_DECODE_CLASS:
		cmd_tables = gen7_video_cmd_table;
		cmd_table_count = ARRAY_SIZE(gen7_video_cmd_table);
		engine->get_cmd_length_mask = gen7_bsd_get_cmd_length_mask;
		break;
	case COPY_ENGINE_CLASS:
		engine->get_cmd_length_mask = gen7_blt_get_cmd_length_mask;
		if (IS_GEN(engine->i915, 9)) {
			cmd_tables = gen9_blt_cmd_table;
			cmd_table_count = ARRAY_SIZE(gen9_blt_cmd_table);
			engine->get_cmd_length_mask =
				gen9_blt_get_cmd_length_mask;

			/* BCS Engine unsafe without parser */
			engine->flags |= I915_ENGINE_REQUIRES_CMD_PARSER;
		} else if (IS_HASWELL(engine->i915)) {
			cmd_tables = hsw_blt_ring_cmd_table;
			cmd_table_count = ARRAY_SIZE(hsw_blt_ring_cmd_table);
		} else {
			cmd_tables = gen7_blt_cmd_table;
			cmd_table_count = ARRAY_SIZE(gen7_blt_cmd_table);
		}

		if (IS_GEN(engine->i915, 9)) {
			engine->reg_tables = gen9_blt_reg_tables;
			engine->reg_table_count =
				ARRAY_SIZE(gen9_blt_reg_tables);
		} else if (IS_HASWELL(engine->i915)) {
			engine->reg_tables = hsw_blt_reg_tables;
			engine->reg_table_count = ARRAY_SIZE(hsw_blt_reg_tables);
		} else {
			engine->reg_tables = ivb_blt_reg_tables;
			engine->reg_table_count = ARRAY_SIZE(ivb_blt_reg_tables);
		}
		break;
	case VIDEO_ENHANCEMENT_CLASS:
		cmd_tables = hsw_vebox_cmd_table;
		cmd_table_count = ARRAY_SIZE(hsw_vebox_cmd_table);
		/* VECS can use the same length_mask function as VCS */
		engine->get_cmd_length_mask = gen7_bsd_get_cmd_length_mask;
		break;
	default:
		MISSING_CASE(engine->class);
		return;
	}

	if (!validate_cmds_sorted(engine, cmd_tables, cmd_table_count)) {
		DRM_ERROR("%s: command descriptions are not sorted\n",
			  engine->name);
		return;
	}
	if (!validate_regs_sorted(engine)) {
		DRM_ERROR("%s: registers are not sorted\n", engine->name);
		return;
	}

	ret = init_hash_table(engine, cmd_tables, cmd_table_count);
	if (ret) {
		DRM_ERROR("%s: initialised failed!\n", engine->name);
		fini_hash_table(engine);
		return;
	}

	engine->flags |= I915_ENGINE_USING_CMD_PARSER;
}