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
 int /*<<< orphan*/  arcmsr_pci_driver ; 
 int pci_register_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arcmsr_module_init(void)
{
	int error = 0;
	error = pci_register_driver(&arcmsr_pci_driver);
	return error;
}