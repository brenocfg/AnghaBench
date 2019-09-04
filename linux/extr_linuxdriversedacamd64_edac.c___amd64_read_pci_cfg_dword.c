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
struct pci_dev {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd64_warn (char*,char const*,int /*<<< orphan*/ ,int) ; 
 int pci_read_config_dword (struct pci_dev*,int,int /*<<< orphan*/ *) ; 

int __amd64_read_pci_cfg_dword(struct pci_dev *pdev, int offset,
			       u32 *val, const char *func)
{
	int err = 0;

	err = pci_read_config_dword(pdev, offset, val);
	if (err)
		amd64_warn("%s: error reading F%dx%03x.\n",
			   func, PCI_FUNC(pdev->devfn), offset);

	return err;
}