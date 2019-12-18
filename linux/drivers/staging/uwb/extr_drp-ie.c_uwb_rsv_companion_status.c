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
struct uwb_rsv {size_t state; } ;

/* Variables and functions */
#define  UWB_RSV_STATE_O_MOVE_EXPANDING 132 
#define  UWB_RSV_STATE_T_EXPANDING_ACCEPTED 131 
#define  UWB_RSV_STATE_T_EXPANDING_CONFLICT 130 
#define  UWB_RSV_STATE_T_EXPANDING_DENIED 129 
#define  UWB_RSV_STATE_T_EXPANDING_PENDING 128 

int uwb_rsv_companion_status(struct uwb_rsv *rsv)
{
	static const int companion_statuses[] = {
		[UWB_RSV_STATE_O_MOVE_EXPANDING]     = 0,
		[UWB_RSV_STATE_T_EXPANDING_ACCEPTED] = 1,
		[UWB_RSV_STATE_T_EXPANDING_CONFLICT] = 0,
		[UWB_RSV_STATE_T_EXPANDING_PENDING]  = 0,
		[UWB_RSV_STATE_T_EXPANDING_DENIED]   = 0,
	};

	return companion_statuses[rsv->state];
}