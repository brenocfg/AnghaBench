#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct bridge_controller {TYPE_3__* base; } ;
struct TYPE_5__ {int /*<<< orphan*/  w_tflush; } ;
struct TYPE_6__ {TYPE_2__ b_widget; TYPE_1__* b_device; } ;
typedef  TYPE_3__ bridge_t ;
struct TYPE_4__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 struct bridge_controller* BRIDGE_CONTROLLER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRIDGE_DEV_SWAP_DIR ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pci_disable_swapping(struct pci_dev *dev)
{
	struct bridge_controller *bc = BRIDGE_CONTROLLER(dev->bus);
	bridge_t *bridge = bc->base;
	int slot = PCI_SLOT(dev->devfn);

	/* Turn off byte swapping */
	bridge->b_device[slot].reg &= ~BRIDGE_DEV_SWAP_DIR;
	bridge->b_widget.w_tflush;	/* Flush */
}