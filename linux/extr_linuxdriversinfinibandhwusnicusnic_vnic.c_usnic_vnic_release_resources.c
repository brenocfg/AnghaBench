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
struct usnic_vnic {TYPE_1__* bar; int /*<<< orphan*/  vdev; int /*<<< orphan*/ * chunks; } ;
struct pci_dev {int dummy; } ;
typedef  enum usnic_vnic_res_type { ____Placeholder_usnic_vnic_res_type } usnic_vnic_res_type ;
struct TYPE_2__ {int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int IORESOURCE_MEM ; 
 int USNIC_VNIC_RES_TYPE_EOL ; 
 int USNIC_VNIC_RES_TYPE_MAX ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 int /*<<< orphan*/  usnic_vnic_free_res_chunk (int /*<<< orphan*/ *) ; 
 struct pci_dev* usnic_vnic_get_pdev (struct usnic_vnic*) ; 
 int /*<<< orphan*/  vnic_dev_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usnic_vnic_release_resources(struct usnic_vnic *vnic)
{
	int i;
	struct pci_dev *pdev;
	enum usnic_vnic_res_type res_type;

	pdev = usnic_vnic_get_pdev(vnic);

	for (res_type = USNIC_VNIC_RES_TYPE_EOL + 1;
			res_type < USNIC_VNIC_RES_TYPE_MAX; res_type++)
		usnic_vnic_free_res_chunk(&vnic->chunks[res_type]);

	vnic_dev_unregister(vnic->vdev);

	for (i = 0; i < ARRAY_SIZE(vnic->bar); i++) {
		if (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM))
			continue;
		iounmap(vnic->bar[i].vaddr);
	}
}