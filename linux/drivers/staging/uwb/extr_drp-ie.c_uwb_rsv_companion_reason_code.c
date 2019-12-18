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
#define  UWB_DRP_REASON_ACCEPTED 136 
#define  UWB_DRP_REASON_CONFLICT 135 
#define  UWB_DRP_REASON_DENIED 134 
#define  UWB_DRP_REASON_PENDING 133 
#define  UWB_RSV_STATE_O_MOVE_EXPANDING 132 
#define  UWB_RSV_STATE_T_EXPANDING_ACCEPTED 131 
#define  UWB_RSV_STATE_T_EXPANDING_CONFLICT 130 
#define  UWB_RSV_STATE_T_EXPANDING_DENIED 129 
#define  UWB_RSV_STATE_T_EXPANDING_PENDING 128 

__attribute__((used)) static int uwb_rsv_companion_reason_code(struct uwb_rsv *rsv)
{
	static const int companion_reason_codes[] = {
		[UWB_RSV_STATE_O_MOVE_EXPANDING]     = UWB_DRP_REASON_ACCEPTED,
		[UWB_RSV_STATE_T_EXPANDING_ACCEPTED] = UWB_DRP_REASON_ACCEPTED,
		[UWB_RSV_STATE_T_EXPANDING_CONFLICT] = UWB_DRP_REASON_CONFLICT,
		[UWB_RSV_STATE_T_EXPANDING_PENDING]  = UWB_DRP_REASON_PENDING,
		[UWB_RSV_STATE_T_EXPANDING_DENIED]   = UWB_DRP_REASON_DENIED,
	};

	return companion_reason_codes[rsv->state];
}