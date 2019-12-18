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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct ocxl_fn {int /*<<< orphan*/  link; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocxl_link_release (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void deconfigure_function(struct ocxl_fn *fn)
{
	struct pci_dev *dev = to_pci_dev(fn->dev.parent);

	ocxl_link_release(dev, fn->link);
	pci_disable_device(dev);
}