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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  dt_fixup_cpu_clocks (int,int,int) ; 
 void* finddevice (char*) ; 
 int /*<<< orphan*/  setprop (void*,char*,int*,int) ; 

void mpc8xx_set_clocks(u32 sysclk)
{
	void *node;

	dt_fixup_cpu_clocks(sysclk, sysclk / 16, sysclk);

	node = finddevice("/soc/cpm");
	if (node)
		setprop(node, "clock-frequency", &sysclk, 4);

	node = finddevice("/soc/cpm/brg");
	if (node)
		setprop(node, "clock-frequency", &sysclk, 4);
}