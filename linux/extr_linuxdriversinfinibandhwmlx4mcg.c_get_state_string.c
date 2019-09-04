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
typedef  enum mcast_group_state { ____Placeholder_mcast_group_state } mcast_group_state ;

/* Variables and functions */
#define  MCAST_IDLE 131 
#define  MCAST_JOIN_SENT 130 
#define  MCAST_LEAVE_SENT 129 
#define  MCAST_RESP_READY 128 

__attribute__((used)) static const char *get_state_string(enum mcast_group_state state)
{
	switch (state) {
	case MCAST_IDLE:
		return "MCAST_IDLE";
	case MCAST_JOIN_SENT:
		return "MCAST_JOIN_SENT";
	case MCAST_LEAVE_SENT:
		return "MCAST_LEAVE_SENT";
	case MCAST_RESP_READY:
		return "MCAST_RESP_READY";
	}
	return "Invalid State";
}