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
 int SID_ARRAY_SIZE ; 
 int /*<<< orphan*/ * dirty_space_id ; 
 scalar_t__ dirty_space_ids ; 
 int /*<<< orphan*/  free_space_ids ; 
 int /*<<< orphan*/ * space_id ; 
 scalar_t__ space_id_index ; 

__attribute__((used)) static void recycle_sids(void)
{
	int i;

	/* NOTE: sid_lock must be held upon entry */

	if (dirty_space_ids != 0) {
		for (i = 0; i < SID_ARRAY_SIZE; i++) {
			space_id[i] ^= dirty_space_id[i];
			dirty_space_id[i] = 0;
		}

		free_space_ids += dirty_space_ids;
		dirty_space_ids = 0;
		space_id_index = 0;
	}
}