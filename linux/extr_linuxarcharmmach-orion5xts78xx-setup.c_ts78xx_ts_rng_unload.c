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
 int /*<<< orphan*/  platform_device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts78xx_ts_rng_device ; 

__attribute__((used)) static void ts78xx_ts_rng_unload(void)
{
	platform_device_del(&ts78xx_ts_rng_device);
}