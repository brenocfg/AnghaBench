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
struct i915_timeline {int /*<<< orphan*/  link; int /*<<< orphan*/  sync; int /*<<< orphan*/  requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  i915_syncmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void i915_timeline_fini(struct i915_timeline *timeline)
{
	GEM_BUG_ON(!list_empty(&timeline->requests));

	i915_syncmap_free(&timeline->sync);

	list_del(&timeline->link);
}