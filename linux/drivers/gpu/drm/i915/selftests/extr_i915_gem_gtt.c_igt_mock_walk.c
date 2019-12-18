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
struct TYPE_2__ {int /*<<< orphan*/  i915; } ;
struct i915_ggtt {TYPE_1__ vm; } ;

/* Variables and functions */
 int exercise_mock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_hole ; 

__attribute__((used)) static int igt_mock_walk(void *arg)
{
	struct i915_ggtt *ggtt = arg;

	return exercise_mock(ggtt->vm.i915, walk_hole);
}