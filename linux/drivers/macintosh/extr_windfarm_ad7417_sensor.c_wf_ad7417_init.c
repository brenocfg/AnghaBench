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
 int ENODEV ; 
 int i2c_add_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  wf_ad7417_driver ; 

__attribute__((used)) static int wf_ad7417_init(void)
{
	/* This is only supported on these machines */
	if (!of_machine_is_compatible("PowerMac7,2") &&
	    !of_machine_is_compatible("PowerMac7,3") &&
	    !of_machine_is_compatible("RackMac3,1"))
		return -ENODEV;

	return i2c_add_driver(&wf_ad7417_driver);
}