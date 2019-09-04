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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 
#define  __HLS_DN_DISABLE_BP 138 
#define  __HLS_DN_DOWNDEF_BP 137 
#define  __HLS_DN_OFFLINE_BP 136 
#define  __HLS_DN_POLL_BP 135 
#define  __HLS_GOING_OFFLINE_BP 134 
#define  __HLS_GOING_UP_BP 133 
#define  __HLS_LINK_COOLDOWN_BP 132 
#define  __HLS_UP_ACTIVE_BP 131 
#define  __HLS_UP_ARMED_BP 130 
#define  __HLS_UP_INIT_BP 129 
#define  __HLS_VERIFY_CAP_BP 128 
 int ilog2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *link_state_name(u32 state)
{
	const char *name;
	int n = ilog2(state);
	static const char * const names[] = {
		[__HLS_UP_INIT_BP]	 = "INIT",
		[__HLS_UP_ARMED_BP]	 = "ARMED",
		[__HLS_UP_ACTIVE_BP]	 = "ACTIVE",
		[__HLS_DN_DOWNDEF_BP]	 = "DOWNDEF",
		[__HLS_DN_POLL_BP]	 = "POLL",
		[__HLS_DN_DISABLE_BP]	 = "DISABLE",
		[__HLS_DN_OFFLINE_BP]	 = "OFFLINE",
		[__HLS_VERIFY_CAP_BP]	 = "VERIFY_CAP",
		[__HLS_GOING_UP_BP]	 = "GOING_UP",
		[__HLS_GOING_OFFLINE_BP] = "GOING_OFFLINE",
		[__HLS_LINK_COOLDOWN_BP] = "LINK_COOLDOWN"
	};

	name = n < ARRAY_SIZE(names) ? names[n] : NULL;
	return name ? name : "unknown";
}