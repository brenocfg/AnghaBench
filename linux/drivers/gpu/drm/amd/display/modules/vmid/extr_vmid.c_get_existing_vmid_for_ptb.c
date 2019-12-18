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
typedef  scalar_t__ uint64_t ;
struct core_vmid {int num_vmid; scalar_t__* ptb_assigned_to_vmid; } ;

/* Variables and functions */

__attribute__((used)) static int get_existing_vmid_for_ptb(struct core_vmid *core_vmid, uint64_t ptb)
{
	int i;

	for (i = 0; i < core_vmid->num_vmid; i++) {
		if (core_vmid->ptb_assigned_to_vmid[i] == ptb)
			return i;
	}

	return -1;
}