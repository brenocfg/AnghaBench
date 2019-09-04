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
 int /*<<< orphan*/  __xor_altivec_4 (unsigned long,unsigned long*,unsigned long*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  disable_kernel_altivec () ; 
 int /*<<< orphan*/  enable_kernel_altivec () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void xor_altivec_4(unsigned long bytes,  unsigned long *v1_in,
		   unsigned long *v2_in, unsigned long *v3_in,
		   unsigned long *v4_in)
{
	preempt_disable();
	enable_kernel_altivec();
	__xor_altivec_4(bytes, v1_in, v2_in, v3_in, v4_in);
	disable_kernel_altivec();
	preempt_enable();
}