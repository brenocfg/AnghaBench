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
struct TYPE_2__ {int /*<<< orphan*/  ioremap; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowa_ioremap ; 
 int /*<<< orphan*/  iowa_pci_io ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  ppc_pci_io ; 

__attribute__((used)) static void io_workaround_init(void)
{
	static int io_workaround_inited;

	if (io_workaround_inited)
		return;
	ppc_pci_io = iowa_pci_io;
	ppc_md.ioremap = iowa_ioremap;
	io_workaround_inited = 1;
}