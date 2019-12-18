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
struct intel_uncore {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_RAW_READ_MMIO_VFUNCS (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSIGN_RAW_WRITE_MMIO_VFUNCS (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen2 ; 
 int /*<<< orphan*/  gen5 ; 
 int /*<<< orphan*/  intel_uncore_has_forcewake (struct intel_uncore*) ; 

__attribute__((used)) static void uncore_raw_init(struct intel_uncore *uncore)
{
	GEM_BUG_ON(intel_uncore_has_forcewake(uncore));

	if (IS_GEN(uncore->i915, 5)) {
		ASSIGN_RAW_WRITE_MMIO_VFUNCS(uncore, gen5);
		ASSIGN_RAW_READ_MMIO_VFUNCS(uncore, gen5);
	} else {
		ASSIGN_RAW_WRITE_MMIO_VFUNCS(uncore, gen2);
		ASSIGN_RAW_READ_MMIO_VFUNCS(uncore, gen2);
	}
}