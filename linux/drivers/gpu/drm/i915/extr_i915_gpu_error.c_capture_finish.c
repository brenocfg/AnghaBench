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
struct i915_gpu_state {TYPE_1__* i915; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* clear_range ) (TYPE_3__*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  start; } ;
struct i915_ggtt {TYPE_3__ vm; TYPE_2__ error_capture; } ;
struct TYPE_4__ {struct i915_ggtt ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void capture_finish(struct i915_gpu_state *error)
{
	struct i915_ggtt *ggtt = &error->i915->ggtt;
	const u64 slot = ggtt->error_capture.start;

	ggtt->vm.clear_range(&ggtt->vm, slot, PAGE_SIZE);
}