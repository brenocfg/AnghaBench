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
#define  UWB_DRP_REASON_ACCEPTED 149 
#define  UWB_DRP_REASON_CONFLICT 148 
#define  UWB_DRP_REASON_DENIED 147 
#define  UWB_DRP_REASON_MODIFIED 146 
#define  UWB_DRP_REASON_PENDING 145 
#define  UWB_RSV_STATE_O_ESTABLISHED 144 
#define  UWB_RSV_STATE_O_INITIATED 143 
#define  UWB_RSV_STATE_O_MODIFIED 142 
#define  UWB_RSV_STATE_O_MOVE_COMBINING 141 
#define  UWB_RSV_STATE_O_MOVE_EXPANDING 140 
#define  UWB_RSV_STATE_O_MOVE_REDUCING 139 
#define  UWB_RSV_STATE_O_PENDING 138 
#define  UWB_RSV_STATE_O_TO_BE_MOVED 137 
#define  UWB_RSV_STATE_T_ACCEPTED 136 
#define  UWB_RSV_STATE_T_CONFLICT 135 
#define  UWB_RSV_STATE_T_DENIED 134 
#define  UWB_RSV_STATE_T_EXPANDING_ACCEPTED 133 
#define  UWB_RSV_STATE_T_EXPANDING_CONFLICT 132 
#define  UWB_RSV_STATE_T_EXPANDING_DENIED 131 
#define  UWB_RSV_STATE_T_EXPANDING_PENDING 130 
#define  UWB_RSV_STATE_T_PENDING 129 
#define  UWB_RSV_STATE_T_RESIZED 128 

__attribute__((used)) static int uwb_rsv_reason_code(struct uwb_rsv *rsv)
{
	static const int reason_codes[] = {
		[UWB_RSV_STATE_O_INITIATED]          = UWB_DRP_REASON_ACCEPTED,
		[UWB_RSV_STATE_O_PENDING]            = UWB_DRP_REASON_ACCEPTED,
		[UWB_RSV_STATE_O_MODIFIED]           = UWB_DRP_REASON_MODIFIED,
		[UWB_RSV_STATE_O_ESTABLISHED]        = UWB_DRP_REASON_ACCEPTED,
		[UWB_RSV_STATE_O_TO_BE_MOVED]        = UWB_DRP_REASON_ACCEPTED,
		[UWB_RSV_STATE_O_MOVE_COMBINING]     = UWB_DRP_REASON_MODIFIED,
		[UWB_RSV_STATE_O_MOVE_REDUCING]      = UWB_DRP_REASON_MODIFIED,
		[UWB_RSV_STATE_O_MOVE_EXPANDING]     = UWB_DRP_REASON_ACCEPTED,
		[UWB_RSV_STATE_T_ACCEPTED]           = UWB_DRP_REASON_ACCEPTED,
		[UWB_RSV_STATE_T_CONFLICT]           = UWB_DRP_REASON_CONFLICT,
		[UWB_RSV_STATE_T_PENDING]            = UWB_DRP_REASON_PENDING,
		[UWB_RSV_STATE_T_DENIED]             = UWB_DRP_REASON_DENIED,
		[UWB_RSV_STATE_T_RESIZED]            = UWB_DRP_REASON_ACCEPTED,
		[UWB_RSV_STATE_T_EXPANDING_ACCEPTED] = UWB_DRP_REASON_ACCEPTED,
		[UWB_RSV_STATE_T_EXPANDING_CONFLICT] = UWB_DRP_REASON_CONFLICT,
		[UWB_RSV_STATE_T_EXPANDING_PENDING]  = UWB_DRP_REASON_PENDING,
		[UWB_RSV_STATE_T_EXPANDING_DENIED]   = UWB_DRP_REASON_DENIED,
	};

	return reason_codes[rsv->state];
}