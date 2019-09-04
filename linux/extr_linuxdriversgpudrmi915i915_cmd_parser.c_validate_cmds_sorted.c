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
typedef  scalar_t__ u32 ;
struct intel_engine_cs {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct drm_i915_cmd_table {int count; struct drm_i915_cmd_descriptor* table; } ;
struct TYPE_2__ {scalar_t__ value; scalar_t__ mask; } ;
struct drm_i915_cmd_descriptor {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool validate_cmds_sorted(const struct intel_engine_cs *engine,
				 const struct drm_i915_cmd_table *cmd_tables,
				 int cmd_table_count)
{
	int i;
	bool ret = true;

	if (!cmd_tables || cmd_table_count == 0)
		return true;

	for (i = 0; i < cmd_table_count; i++) {
		const struct drm_i915_cmd_table *table = &cmd_tables[i];
		u32 previous = 0;
		int j;

		for (j = 0; j < table->count; j++) {
			const struct drm_i915_cmd_descriptor *desc =
				&table->table[j];
			u32 curr = desc->cmd.value & desc->cmd.mask;

			if (curr < previous) {
				DRM_ERROR("CMD: %s [%d] command table not sorted: "
					  "table=%d entry=%d cmd=0x%08X prev=0x%08X\n",
					  engine->name, engine->id,
					  i, j, curr, previous);
				ret = false;
			}

			previous = curr;
		}
	}

	return ret;
}