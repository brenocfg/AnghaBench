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
typedef  int u32 ;
struct intel_runtime_info {int* platform_mask; } ;
typedef  enum intel_platform { ____Placeholder_intel_platform } intel_platform ;

/* Variables and functions */
 int INTEL_SUBPLATFORM_BITS ; 
 unsigned int __platform_mask_index (struct intel_runtime_info const*,int) ; 

__attribute__((used)) static inline u32
intel_subplatform(const struct intel_runtime_info *info, enum intel_platform p)
{
	const unsigned int pi = __platform_mask_index(info, p);

	return info->platform_mask[pi] & INTEL_SUBPLATFORM_BITS;
}