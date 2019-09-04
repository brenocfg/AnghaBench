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
typedef  enum mei_hbm_state { ____Placeholder_mei_hbm_state } mei_hbm_state ;

/* Variables and functions */
#define  MEI_HBM_CLIENT_PROPERTIES 133 
#define  MEI_HBM_ENUM_CLIENTS 132 
#define  MEI_HBM_IDLE 131 
#define  MEI_HBM_STARTED 130 
#define  MEI_HBM_STARTING 129 
#define  MEI_HBM_STOPPED 128 

const char *mei_hbm_state_str(enum mei_hbm_state state)
{
#define MEI_HBM_STATE(state) case MEI_HBM_##state: return #state
	switch (state) {
	MEI_HBM_STATE(IDLE);
	MEI_HBM_STATE(STARTING);
	MEI_HBM_STATE(STARTED);
	MEI_HBM_STATE(ENUM_CLIENTS);
	MEI_HBM_STATE(CLIENT_PROPERTIES);
	MEI_HBM_STATE(STOPPED);
	default:
		return "unknown";
	}
#undef MEI_HBM_STATE
}