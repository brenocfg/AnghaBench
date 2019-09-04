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
 int /*<<< orphan*/  KVM_HC_MIPS_CONSOLE_OUTPUT ; 
 int /*<<< orphan*/  kvm_hypercall3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int) ; 

void prom_putchar(char c)
{
	kvm_hypercall3(KVM_HC_MIPS_CONSOLE_OUTPUT, 0 /*  port 0 */,
		(unsigned long)&c, 1 /* len == 1 */);
}