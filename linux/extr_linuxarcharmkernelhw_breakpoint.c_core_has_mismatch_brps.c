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
 scalar_t__ ARM_DEBUG_ARCH_V7_ECP14 ; 
 scalar_t__ get_debug_arch () ; 
 int get_num_brp_resources () ; 

__attribute__((used)) static int core_has_mismatch_brps(void)
{
	return (get_debug_arch() >= ARM_DEBUG_ARCH_V7_ECP14 &&
		get_num_brp_resources() > 1);
}