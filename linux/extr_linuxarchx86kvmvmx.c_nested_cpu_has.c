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
struct vmcs12 {int cpu_based_vm_exec_control; } ;

/* Variables and functions */

__attribute__((used)) static inline bool nested_cpu_has(struct vmcs12 *vmcs12, u32 bit)
{
	return vmcs12->cpu_based_vm_exec_control & bit;
}