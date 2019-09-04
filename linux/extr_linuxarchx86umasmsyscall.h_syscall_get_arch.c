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
 int AUDIT_ARCH_X86_64 ; 

__attribute__((used)) static inline int syscall_get_arch(void)
{
#ifdef CONFIG_X86_32
	return AUDIT_ARCH_I386;
#else
	return AUDIT_ARCH_X86_64;
#endif
}