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
typedef  enum mei_pg_state { ____Placeholder_mei_pg_state } mei_pg_state ;

/* Variables and functions */
#define  MEI_PG_OFF 129 
#define  MEI_PG_ON 128 

const char *mei_pg_state_str(enum mei_pg_state state)
{
#define MEI_PG_STATE(state) case MEI_PG_##state: return #state
	switch (state) {
	MEI_PG_STATE(OFF);
	MEI_PG_STATE(ON);
	default:
		return "unknown";
	}
#undef MEI_PG_STATE
}