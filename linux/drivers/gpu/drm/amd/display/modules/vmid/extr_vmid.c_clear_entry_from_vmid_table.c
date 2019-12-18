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
struct core_vmid {int /*<<< orphan*/  num_vmids_available; scalar_t__* ptb_assigned_to_vmid; } ;

/* Variables and functions */

__attribute__((used)) static void clear_entry_from_vmid_table(struct core_vmid *core_vmid, unsigned int vmid)
{
	core_vmid->ptb_assigned_to_vmid[vmid] = 0;
	core_vmid->num_vmids_available++;
}