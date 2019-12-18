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
struct TYPE_2__ {scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  enter (char*) ; 
 int /*<<< orphan*/  i82092aa_pci_driver ; 
 int /*<<< orphan*/  leave (char*) ; 
 int /*<<< orphan*/  pci_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 TYPE_1__* sockets ; 

__attribute__((used)) static void i82092aa_module_exit(void)
{
	enter("i82092aa_module_exit");
	pci_unregister_driver(&i82092aa_pci_driver);
	if (sockets[0].io_base>0)
			 release_region(sockets[0].io_base, 2);
	leave("i82092aa_module_exit");
}