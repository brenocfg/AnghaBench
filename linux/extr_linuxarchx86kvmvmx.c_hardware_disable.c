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
 int /*<<< orphan*/  kvm_cpu_vmxoff () ; 
 int /*<<< orphan*/  vmclear_local_loaded_vmcss () ; 

__attribute__((used)) static void hardware_disable(void)
{
	vmclear_local_loaded_vmcss();
	kvm_cpu_vmxoff();
}