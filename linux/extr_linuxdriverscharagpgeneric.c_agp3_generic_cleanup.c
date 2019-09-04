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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ capndx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AGPCTRL ; 
 int AGPCTRL_APERENB ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,scalar_t__,int) ; 

void agp3_generic_cleanup(void)
{
	u32 ctrl;
	pci_read_config_dword(agp_bridge->dev, agp_bridge->capndx+AGPCTRL, &ctrl);
	pci_write_config_dword(agp_bridge->dev, agp_bridge->capndx+AGPCTRL, ctrl & ~AGPCTRL_APERENB);
}