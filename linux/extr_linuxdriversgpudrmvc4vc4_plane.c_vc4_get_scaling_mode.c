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
typedef  scalar_t__ u32 ;
typedef  enum vc4_scaling_mode { ____Placeholder_vc4_scaling_mode } vc4_scaling_mode ;

/* Variables and functions */
 int VC4_SCALING_NONE ; 
 int VC4_SCALING_PPF ; 
 int VC4_SCALING_TPZ ; 

__attribute__((used)) static enum vc4_scaling_mode vc4_get_scaling_mode(u32 src, u32 dst)
{
	if (dst > src)
		return VC4_SCALING_PPF;
	else if (dst < src)
		return VC4_SCALING_TPZ;
	else
		return VC4_SCALING_NONE;
}