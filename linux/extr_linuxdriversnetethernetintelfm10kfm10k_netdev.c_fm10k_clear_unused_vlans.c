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
typedef  scalar_t__ u32 ;
struct fm10k_intfc {int dummy; } ;

/* Variables and functions */
 scalar_t__ FM10K_VLAN_LENGTH_SHIFT ; 
 scalar_t__ VLAN_N_VID ; 
 scalar_t__ fm10k_find_next_vlan (struct fm10k_intfc*,scalar_t__) ; 
 int /*<<< orphan*/  fm10k_queue_vlan_request (struct fm10k_intfc*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fm10k_clear_unused_vlans(struct fm10k_intfc *interface)
{
	u32 vid, prev_vid;

	/* loop through and find any gaps in the table */
	for (vid = 0, prev_vid = 0;
	     prev_vid < VLAN_N_VID;
	     prev_vid = vid + 1, vid = fm10k_find_next_vlan(interface, vid)) {
		if (prev_vid == vid)
			continue;

		/* send request to clear multiple bits at a time */
		prev_vid += (vid - prev_vid - 1) << FM10K_VLAN_LENGTH_SHIFT;
		fm10k_queue_vlan_request(interface, prev_vid, 0, false);
	}
}