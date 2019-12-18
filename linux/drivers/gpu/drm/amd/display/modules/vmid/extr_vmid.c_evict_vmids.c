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
typedef  unsigned int uint16_t ;
struct core_vmid {int num_vmid; int /*<<< orphan*/  dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_entry_from_vmid_table (struct core_vmid*,int) ; 
 unsigned int dc_get_vmid_use_vector (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void evict_vmids(struct core_vmid *core_vmid)
{
	int i;
	uint16_t ord = dc_get_vmid_use_vector(core_vmid->dc);

	// At this point any positions with value 0 are unused vmids, evict them
	for (i = 1; i < core_vmid->num_vmid; i++) {
		if (ord & (1u << i))
			clear_entry_from_vmid_table(core_vmid, i);
	}
}