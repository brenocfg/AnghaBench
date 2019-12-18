#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* vma; } ;
struct intel_guc {TYPE_2__ log; } ;
struct intel_uc {scalar_t__ load_err_log; struct intel_guc guc; } ;
struct TYPE_3__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 scalar_t__ i915_gem_object_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __uc_capture_load_err_log(struct intel_uc *uc)
{
	struct intel_guc *guc = &uc->guc;

	if (guc->log.vma && !uc->load_err_log)
		uc->load_err_log = i915_gem_object_get(guc->log.vma->obj);
}