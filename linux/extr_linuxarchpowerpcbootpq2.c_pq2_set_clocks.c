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
 int /*<<< orphan*/  dt_fixup_cpu_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* finddevice (char*) ; 
 int /*<<< orphan*/  setprop (void*,char*,int /*<<< orphan*/ *,int) ; 

void pq2_set_clocks(u32 sysfreq, u32 corefreq, u32 timebase, u32 brgfreq)
{
	void *node;

	dt_fixup_cpu_clocks(corefreq, timebase, sysfreq);

	node = finddevice("/soc/cpm");
	if (node)
		setprop(node, "clock-frequency", &sysfreq, 4);

	node = finddevice("/soc/cpm/brg");
	if (node)
		setprop(node, "clock-frequency", &brgfreq, 4);
}