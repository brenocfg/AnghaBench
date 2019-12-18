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
typedef  int u64 ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_CPU_GTT_USWC ; 
 int /*<<< orphan*/  DRM_INFO_ONCE (char*) ; 
 int /*<<< orphan*/  drm_arch_can_wc_memory () ; 

bool amdgpu_bo_support_uswc(u64 bo_flags)
{

#ifdef CONFIG_X86_32
	/* XXX: Write-combined CPU mappings of GTT seem broken on 32-bit
	 * See https://bugs.freedesktop.org/show_bug.cgi?id=84627
	 */
	return false;
#elif defined(CONFIG_X86) && !defined(CONFIG_X86_PAT)
	/* Don't try to enable write-combining when it can't work, or things
	 * may be slow
	 * See https://bugs.freedesktop.org/show_bug.cgi?id=88758
	 */

#ifndef CONFIG_COMPILE_TEST
#warning Please enable CONFIG_MTRR and CONFIG_X86_PAT for better performance \
	 thanks to write-combining
#endif

	if (bo_flags & AMDGPU_GEM_CREATE_CPU_GTT_USWC)
		DRM_INFO_ONCE("Please enable CONFIG_MTRR and CONFIG_X86_PAT for "
			      "better performance thanks to write-combining\n");
	return false;
#else
	/* For architectures that don't support WC memory,
	 * mask out the WC flag from the BO
	 */
	if (!drm_arch_can_wc_memory())
		return false;

	return true;
#endif
}