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
struct asd_ha_struct {int /*<<< orphan*/  pcidev; struct asd_ha_addrspace* io_handle; } ;
struct asd_ha_addrspace {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asd_unmap_memio(struct asd_ha_struct *asd_ha)
{
	struct asd_ha_addrspace *io_handle;

	io_handle = &asd_ha->io_handle[1];
	iounmap(io_handle->addr);
	pci_release_region(asd_ha->pcidev, 2);

	io_handle = &asd_ha->io_handle[0];
	iounmap(io_handle->addr);
	pci_release_region(asd_ha->pcidev, 0);
}