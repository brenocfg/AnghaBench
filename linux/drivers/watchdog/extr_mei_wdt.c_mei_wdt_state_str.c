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
typedef  enum mei_wdt_state { ____Placeholder_mei_wdt_state } mei_wdt_state ;

/* Variables and functions */
#define  MEI_WDT_IDLE 133 
#define  MEI_WDT_NOT_REQUIRED 132 
#define  MEI_WDT_PROBE 131 
#define  MEI_WDT_RUNNING 130 
#define  MEI_WDT_START 129 
#define  MEI_WDT_STOPPING 128 

__attribute__((used)) static const char *mei_wdt_state_str(enum mei_wdt_state state)
{
	switch (state) {
	case MEI_WDT_PROBE:
		return "PROBE";
	case MEI_WDT_IDLE:
		return "IDLE";
	case MEI_WDT_START:
		return "START";
	case MEI_WDT_RUNNING:
		return "RUNNING";
	case MEI_WDT_STOPPING:
		return "STOPPING";
	case MEI_WDT_NOT_REQUIRED:
		return "NOT_REQUIRED";
	default:
		return "unknown";
	}
}