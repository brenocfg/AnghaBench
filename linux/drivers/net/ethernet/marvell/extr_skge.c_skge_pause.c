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
typedef  enum pause_status { ____Placeholder_pause_status } pause_status ;

/* Variables and functions */
#define  FLOW_STAT_LOC_SEND 131 
#define  FLOW_STAT_NONE 130 
#define  FLOW_STAT_REM_SEND 129 
#define  FLOW_STAT_SYMMETRIC 128 

__attribute__((used)) static const char *skge_pause(enum pause_status status)
{
	switch (status) {
	case FLOW_STAT_NONE:
		return "none";
	case FLOW_STAT_REM_SEND:
		return "rx only";
	case FLOW_STAT_LOC_SEND:
		return "tx_only";
	case FLOW_STAT_SYMMETRIC:		/* Both station may send PAUSE */
		return "both";
	default:
		return "indeterminated";
	}
}