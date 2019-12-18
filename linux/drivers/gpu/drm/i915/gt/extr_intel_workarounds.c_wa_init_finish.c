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
struct i915_wa_list {int count; int /*<<< orphan*/  engine_name; int /*<<< orphan*/  name; int /*<<< orphan*/  wa_count; struct i915_wa* list; } ;
struct i915_wa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WA_LIST_CHUNK ; 
 int /*<<< orphan*/  kfree (struct i915_wa*) ; 
 struct i915_wa* kmemdup (struct i915_wa*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wa_init_finish(struct i915_wa_list *wal)
{
	/* Trim unused entries. */
	if (!IS_ALIGNED(wal->count, WA_LIST_CHUNK)) {
		struct i915_wa *list = kmemdup(wal->list,
					       wal->count * sizeof(*list),
					       GFP_KERNEL);

		if (list) {
			kfree(wal->list);
			wal->list = list;
		}
	}

	if (!wal->count)
		return;

	DRM_DEBUG_DRIVER("Initialized %u %s workarounds on %s\n",
			 wal->wa_count, wal->name, wal->engine_name);
}