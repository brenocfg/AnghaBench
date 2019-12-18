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
 scalar_t__ fb_get_options (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gxt4500_driver ; 
 int /*<<< orphan*/  mode_option ; 
 int pci_register_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gxt4500_init(void)
{
#ifndef MODULE
	if (fb_get_options("gxt4500", &mode_option))
		return -ENODEV;
#endif

	return pci_register_driver(&gxt4500_driver);
}