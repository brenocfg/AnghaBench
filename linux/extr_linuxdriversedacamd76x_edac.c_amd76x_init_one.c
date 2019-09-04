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
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int amd76x_probe1 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int amd76x_init_one(struct pci_dev *pdev,
			   const struct pci_device_id *ent)
{
	edac_dbg(0, "\n");

	/* don't need to call pci_enable_device() */
	return amd76x_probe1(pdev, ent->driver_data);
}