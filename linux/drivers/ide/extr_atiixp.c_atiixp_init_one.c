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
struct pci_device_id {size_t driver_data; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * atiixp_pci_info ; 
 int ide_pci_init_one (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atiixp_init_one(struct pci_dev *dev, const struct pci_device_id *id)
{
	return ide_pci_init_one(dev, &atiixp_pci_info[id->driver_data], NULL);
}