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
struct drm_i915_private {int dummy; } ;
struct drm_i915_mocs_table {int size; TYPE_1__* table; } ;
struct TYPE_2__ {int l3cc_value; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 
 int L3_ESC (int) ; 
 int L3_SCC (int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 void* broxton_mocs_table ; 
 void* skylake_mocs_table ; 

__attribute__((used)) static bool get_mocs_settings(struct drm_i915_private *dev_priv,
			      struct drm_i915_mocs_table *table)
{
	bool result = false;

	if (IS_GEN9_BC(dev_priv) || IS_CANNONLAKE(dev_priv) ||
	    IS_ICELAKE(dev_priv)) {
		table->size  = ARRAY_SIZE(skylake_mocs_table);
		table->table = skylake_mocs_table;
		result = true;
	} else if (IS_GEN9_LP(dev_priv)) {
		table->size  = ARRAY_SIZE(broxton_mocs_table);
		table->table = broxton_mocs_table;
		result = true;
	} else {
		WARN_ONCE(INTEL_GEN(dev_priv) >= 9,
			  "Platform that should have a MOCS table does not.\n");
	}

	/* WaDisableSkipCaching:skl,bxt,kbl,glk */
	if (IS_GEN9(dev_priv)) {
		int i;

		for (i = 0; i < table->size; i++)
			if (WARN_ON(table->table[i].l3cc_value &
				    (L3_ESC(1) | L3_SCC(0x7))))
				return false;
	}

	return result;
}