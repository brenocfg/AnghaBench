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
struct pci_dev {int class; } ;
struct TYPE_2__ {int /*<<< orphan*/  handler_flags; } ;

/* Variables and functions */
 int PCI_BASE_CLASS_DISPLAY ; 
 scalar_t__ apple_gmux_present () ; 
 struct pci_dev* vga_default_device () ; 
 TYPE_1__ vgasr_priv ; 

bool vga_switcheroo_client_probe_defer(struct pci_dev *pdev)
{
	if ((pdev->class >> 16) == PCI_BASE_CLASS_DISPLAY) {
		/*
		 * apple-gmux is needed on pre-retina MacBook Pro
		 * to probe the panel if pdev is the inactive GPU.
		 */
		if (apple_gmux_present() && pdev != vga_default_device() &&
		    !vgasr_priv.handler_flags)
			return true;
	}

	return false;
}