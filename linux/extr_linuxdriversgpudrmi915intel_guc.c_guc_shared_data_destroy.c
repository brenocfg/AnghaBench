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
struct intel_guc {TYPE_1__* shared_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unpin_and_release (TYPE_1__**) ; 

__attribute__((used)) static void guc_shared_data_destroy(struct intel_guc *guc)
{
	i915_gem_object_unpin_map(guc->shared_data->obj);
	i915_vma_unpin_and_release(&guc->shared_data);
}