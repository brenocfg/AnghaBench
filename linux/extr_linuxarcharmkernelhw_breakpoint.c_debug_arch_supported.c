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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ ARM_DEBUG_ARCH_V6 ; 
 scalar_t__ ARM_DEBUG_ARCH_V7_1 ; 
 scalar_t__ ARM_DEBUG_ARCH_V7_ECP14 ; 
 scalar_t__ get_debug_arch () ; 

__attribute__((used)) static int debug_arch_supported(void)
{
	u8 arch = get_debug_arch();

	/* We don't support the memory-mapped interface. */
	return (arch >= ARM_DEBUG_ARCH_V6 && arch <= ARM_DEBUG_ARCH_V7_ECP14) ||
		arch >= ARM_DEBUG_ARCH_V7_1;
}