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
 int STAT_BUSMASK ; 

__attribute__((used)) static const char *fas216_bus_phase(int stat)
{
	static const char *phases[] = {
		"DATA OUT", "DATA IN",
		"COMMAND", "STATUS",
		"MISC OUT", "MISC IN",
		"MESG OUT", "MESG IN"
	};

	return phases[stat & STAT_BUSMASK];
}