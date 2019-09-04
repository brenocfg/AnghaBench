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

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_PKEY ; 
 int /*<<< orphan*/  FW_FEATURE_LPAR ; 
 int cpu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int pkeys_total ; 

__attribute__((used)) static inline bool pkey_mmu_enabled(void)
{
	if (firmware_has_feature(FW_FEATURE_LPAR))
		return pkeys_total;
	else
		return cpu_has_feature(CPU_FTR_PKEY);
}