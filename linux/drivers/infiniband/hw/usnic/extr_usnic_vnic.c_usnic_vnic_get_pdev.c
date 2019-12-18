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
struct usnic_vnic {int /*<<< orphan*/  vdev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct pci_dev* vnic_dev_get_pdev (int /*<<< orphan*/ ) ; 

struct pci_dev *usnic_vnic_get_pdev(struct usnic_vnic *vnic)
{
	return vnic_dev_get_pdev(vnic->vdev);
}