#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ default_ticks; } ;

/* Variables and functions */
 TYPE_1__ cpu5wdt_device ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 scalar_t__ ticks ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void cpu5wdt_reset(void)
{
	ticks = cpu5wdt_device.default_ticks;

	if (verbose)
		pr_debug("reset (%i ticks)\n", (int) ticks);

}