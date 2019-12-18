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
typedef  scalar_t__ u16 ;
struct esas2r_target {scalar_t__ target_state; } ;
struct esas2r_adapter {struct esas2r_target* targetdb; } ;

/* Variables and functions */
 scalar_t__ ESAS2R_MAX_TARGETS ; 
 scalar_t__ TS_PRESENT ; 

u16 esas2r_targ_db_find_next_present(struct esas2r_adapter *a, u16 target_id)
{
	u16 id = target_id + 1;

	while (id < ESAS2R_MAX_TARGETS) {
		struct esas2r_target *t = a->targetdb + id;

		if (t->target_state == TS_PRESENT)
			break;

		id++;
	}

	return id;
}