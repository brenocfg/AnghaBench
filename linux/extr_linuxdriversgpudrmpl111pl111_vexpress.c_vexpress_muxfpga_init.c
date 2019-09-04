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
 int EBUSY ; 
 int platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vexpress_muxfpga_driver ; 

int vexpress_muxfpga_init(void)
{
	int ret;

	ret = platform_driver_register(&vexpress_muxfpga_driver);
	/* -EBUSY just means this driver is already registered */
	if (ret == -EBUSY)
		ret = 0;
	return ret;
}