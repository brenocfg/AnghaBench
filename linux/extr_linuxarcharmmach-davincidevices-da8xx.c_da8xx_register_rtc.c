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
 int /*<<< orphan*/  da8xx_rtc_device ; 
 int platform_device_register (int /*<<< orphan*/ *) ; 

int da8xx_register_rtc(void)
{
	return platform_device_register(&da8xx_rtc_device);
}