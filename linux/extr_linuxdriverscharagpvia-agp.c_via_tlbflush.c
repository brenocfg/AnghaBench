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
struct agp_memory {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIA_GARTCTRL ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void via_tlbflush(struct agp_memory *mem)
{
	u32 temp;

	pci_read_config_dword(agp_bridge->dev, VIA_GARTCTRL, &temp);
	temp |= (1<<7);
	pci_write_config_dword(agp_bridge->dev, VIA_GARTCTRL, temp);
	temp &= ~(1<<7);
	pci_write_config_dword(agp_bridge->dev, VIA_GARTCTRL, temp);
}