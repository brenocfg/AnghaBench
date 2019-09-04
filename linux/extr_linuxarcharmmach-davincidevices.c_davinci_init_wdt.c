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
 int /*<<< orphan*/  davinci_wdt_device ; 
 int platform_device_register (int /*<<< orphan*/ *) ; 

int davinci_init_wdt(void)
{
	return platform_device_register(&davinci_wdt_device);
}