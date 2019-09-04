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
#define  MEI_DEV_DISABLED 134 
#define  MEI_DEV_ENABLED 133 
#define  MEI_DEV_INITIALIZING 132 
#define  MEI_DEV_INIT_CLIENTS 131 
#define  MEI_DEV_POWER_DOWN 130 
#define  MEI_DEV_POWER_UP 129 
#define  MEI_DEV_RESETTING 128 

const char *mei_dev_state_str(int state)
{
#define MEI_DEV_STATE(state) case MEI_DEV_##state: return #state
	switch (state) {
	MEI_DEV_STATE(INITIALIZING);
	MEI_DEV_STATE(INIT_CLIENTS);
	MEI_DEV_STATE(ENABLED);
	MEI_DEV_STATE(RESETTING);
	MEI_DEV_STATE(DISABLED);
	MEI_DEV_STATE(POWER_DOWN);
	MEI_DEV_STATE(POWER_UP);
	default:
		return "unknown";
	}
#undef MEI_DEV_STATE
}