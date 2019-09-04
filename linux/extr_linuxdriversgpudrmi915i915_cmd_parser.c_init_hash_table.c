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
struct intel_engine_cs {int /*<<< orphan*/  cmd_hash; } ;
struct drm_i915_cmd_table {int count; struct drm_i915_cmd_descriptor* table; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct drm_i915_cmd_descriptor {TYPE_1__ cmd; } ;
struct cmd_node {int /*<<< orphan*/  node; struct drm_i915_cmd_descriptor const* desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cmd_header_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 struct cmd_node* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_hash_table(struct intel_engine_cs *engine,
			   const struct drm_i915_cmd_table *cmd_tables,
			   int cmd_table_count)
{
	int i, j;

	hash_init(engine->cmd_hash);

	for (i = 0; i < cmd_table_count; i++) {
		const struct drm_i915_cmd_table *table = &cmd_tables[i];

		for (j = 0; j < table->count; j++) {
			const struct drm_i915_cmd_descriptor *desc =
				&table->table[j];
			struct cmd_node *desc_node =
				kmalloc(sizeof(*desc_node), GFP_KERNEL);

			if (!desc_node)
				return -ENOMEM;

			desc_node->desc = desc;
			hash_add(engine->cmd_hash, &desc_node->node,
				 cmd_header_key(desc->cmd.value));
		}
	}

	return 0;
}