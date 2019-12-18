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
typedef  scalar_t__ u8 ;
struct intel_engine_cs {struct drm_i915_private* i915; } ;
struct i915_wa_list {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * subslice_7eu; } ;
struct TYPE_4__ {TYPE_1__ sseu; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN7_GT_MODE ; 
 int GEN9_IZ_HASHING (int,scalar_t__) ; 
 int GEN9_IZ_HASHING_MASK (int) ; 
 TYPE_2__* RUNTIME_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WA_SET_FIELD_MASKED (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_tune_iz_hashing(struct intel_engine_cs *engine,
				struct i915_wa_list *wal)
{
	struct drm_i915_private *i915 = engine->i915;
	u8 vals[3] = { 0, 0, 0 };
	unsigned int i;

	for (i = 0; i < 3; i++) {
		u8 ss;

		/*
		 * Only consider slices where one, and only one, subslice has 7
		 * EUs
		 */
		if (!is_power_of_2(RUNTIME_INFO(i915)->sseu.subslice_7eu[i]))
			continue;

		/*
		 * subslice_7eu[i] != 0 (because of the check above) and
		 * ss_max == 4 (maximum number of subslices possible per slice)
		 *
		 * ->    0 <= ss <= 3;
		 */
		ss = ffs(RUNTIME_INFO(i915)->sseu.subslice_7eu[i]) - 1;
		vals[i] = 3 - ss;
	}

	if (vals[0] == 0 && vals[1] == 0 && vals[2] == 0)
		return;

	/* Tune IZ hashing. See intel_device_info_runtime_init() */
	WA_SET_FIELD_MASKED(GEN7_GT_MODE,
			    GEN9_IZ_HASHING_MASK(2) |
			    GEN9_IZ_HASHING_MASK(1) |
			    GEN9_IZ_HASHING_MASK(0),
			    GEN9_IZ_HASHING(2, vals[2]) |
			    GEN9_IZ_HASHING(1, vals[1]) |
			    GEN9_IZ_HASHING(0, vals[0]));
}