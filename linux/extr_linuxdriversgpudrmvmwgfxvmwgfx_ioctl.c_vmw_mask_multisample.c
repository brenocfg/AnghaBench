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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 unsigned int SVGA3D_DEVCAP_MULTISAMPLE_MASKABLESAMPLES ; 

__attribute__((used)) static u32 vmw_mask_multisample(unsigned int cap, u32 fmt_value)
{
	/*
	 * A version of user-space exists which use MULTISAMPLE_MASKABLESAMPLES
	 * to check the sample count supported by virtual device. Since there
	 * never was support for multisample count for backing MOB return 0.
	 */
	if (cap == SVGA3D_DEVCAP_MULTISAMPLE_MASKABLESAMPLES)
		return 0;

	return fmt_value;
}