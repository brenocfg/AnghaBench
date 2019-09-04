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
typedef  size_t u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_X86_32 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_AMD64_PATCH_LEVEL ; 
 scalar_t__ __pa_nodebug (size_t**) ; 
 size_t* final_levels ; 
 int /*<<< orphan*/  native_rdmsr (int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static bool amd_check_current_patch_level(void)
{
	u32 lvl, dummy, i;
	u32 *levels;

	native_rdmsr(MSR_AMD64_PATCH_LEVEL, lvl, dummy);

	if (IS_ENABLED(CONFIG_X86_32))
		levels = (u32 *)__pa_nodebug(&final_levels);
	else
		levels = final_levels;

	for (i = 0; levels[i]; i++) {
		if (lvl == levels[i])
			return true;
	}
	return false;
}