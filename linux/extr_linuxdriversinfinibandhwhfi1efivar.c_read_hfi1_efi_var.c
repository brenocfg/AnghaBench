#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hfi1_devdata {TYPE_1__* pcidev; } ;
typedef  int /*<<< orphan*/  prefix_name ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {int number; } ;
struct TYPE_3__ {int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;

/* Variables and functions */
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ isalpha (char) ; 
 int pci_domain_nr (TYPE_2__*) ; 
 int read_efi_var (char*,unsigned long*,void**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 char toupper (char) ; 

int read_hfi1_efi_var(struct hfi1_devdata *dd, const char *kind,
		      unsigned long *size, void **return_data)
{
	char prefix_name[64];
	char name[64];
	int result;
	int i;

	/* create a common prefix */
	snprintf(prefix_name, sizeof(prefix_name), "%04x:%02x:%02x.%x",
		 pci_domain_nr(dd->pcidev->bus),
		 dd->pcidev->bus->number,
		 PCI_SLOT(dd->pcidev->devfn),
		 PCI_FUNC(dd->pcidev->devfn));
	snprintf(name, sizeof(name), "%s-%s", prefix_name, kind);
	result = read_efi_var(name, size, return_data);

	/*
	 * If reading the lowercase EFI variable fail, read the uppercase
	 * variable.
	 */
	if (result) {
		/* Converting to uppercase */
		for (i = 0; prefix_name[i]; i++)
			if (isalpha(prefix_name[i]))
				prefix_name[i] = toupper(prefix_name[i]);
		snprintf(name, sizeof(name), "%s-%s", prefix_name, kind);
		result = read_efi_var(name, size, return_data);
	}

	return result;
}