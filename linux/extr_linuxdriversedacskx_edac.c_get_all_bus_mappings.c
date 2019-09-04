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
typedef  int /*<<< orphan*/  u32 ;
struct skx_dev {int /*<<< orphan*/  list; void** bus; int /*<<< orphan*/  seg; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  edac_dbg (int,char*,void*,void*,void*,void*) ; 
 struct skx_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skx_edac_list ; 
 int /*<<< orphan*/  skx_num_sockets ; 

__attribute__((used)) static int get_all_bus_mappings(void)
{
	struct pci_dev *pdev, *prev;
	struct skx_dev *d;
	u32 reg;
	int ndev = 0;

	prev = NULL;
	for (;;) {
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x2016, prev);
		if (!pdev)
			break;
		ndev++;
		d = kzalloc(sizeof(*d), GFP_KERNEL);
		if (!d) {
			pci_dev_put(pdev);
			return -ENOMEM;
		}
		d->seg = pci_domain_nr(pdev->bus);
		pci_read_config_dword(pdev, 0xCC, &reg);
		d->bus[0] =  GET_BITFIELD(reg, 0, 7);
		d->bus[1] =  GET_BITFIELD(reg, 8, 15);
		d->bus[2] =  GET_BITFIELD(reg, 16, 23);
		d->bus[3] =  GET_BITFIELD(reg, 24, 31);
		edac_dbg(2, "busses: %x, %x, %x, %x\n",
			 d->bus[0], d->bus[1], d->bus[2], d->bus[3]);
		list_add_tail(&d->list, &skx_edac_list);
		skx_num_sockets++;
		prev = pdev;
	}

	return ndev;
}