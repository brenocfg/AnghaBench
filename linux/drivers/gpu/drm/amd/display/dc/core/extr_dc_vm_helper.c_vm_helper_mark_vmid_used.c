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
typedef  size_t uint8_t ;
struct vmid_usage {int* vmid_usage; } ;
struct vm_helper {struct vmid_usage* hubp_vmid_usage; } ;

/* Variables and functions */

void vm_helper_mark_vmid_used(struct vm_helper *vm_helper, unsigned int pos, uint8_t hubp_idx)
{
	struct vmid_usage vmids = vm_helper->hubp_vmid_usage[hubp_idx];

	vmids.vmid_usage[0] = vmids.vmid_usage[1];
	vmids.vmid_usage[1] = 1 << pos;
}