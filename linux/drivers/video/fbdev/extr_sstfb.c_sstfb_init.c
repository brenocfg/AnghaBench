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
 scalar_t__ fb_get_options (char*,char**) ; 
 int pci_register_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sstfb_driver ; 
 int /*<<< orphan*/  sstfb_setup (char*) ; 

__attribute__((used)) static int sstfb_init(void)
{
	char *option = NULL;

	if (fb_get_options("sstfb", &option))
		return -ENODEV;
	sstfb_setup(option);

	return pci_register_driver(&sstfb_driver);
}