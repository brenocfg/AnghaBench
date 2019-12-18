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
typedef  int /*<<< orphan*/  uint64_t ;
struct core_vmid {int /*<<< orphan*/  num_vmids_available; int /*<<< orphan*/ * ptb_assigned_to_vmid; } ;

/* Variables and functions */

__attribute__((used)) static void add_ptb_to_table(struct core_vmid *core_vmid, unsigned int vmid, uint64_t ptb)
{
	core_vmid->ptb_assigned_to_vmid[vmid] = ptb;
	core_vmid->num_vmids_available--;
}