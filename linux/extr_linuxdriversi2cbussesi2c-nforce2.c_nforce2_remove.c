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
struct pci_dev {int dummy; } ;
struct nforce2_smbus {int /*<<< orphan*/  size; scalar_t__ base; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nforce2_smbus*) ; 
 int /*<<< orphan*/  nforce2_set_reference (int /*<<< orphan*/ *) ; 
 struct nforce2_smbus* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nforce2_remove(struct pci_dev *dev)
{
	struct nforce2_smbus *smbuses = pci_get_drvdata(dev);

	nforce2_set_reference(NULL);
	if (smbuses[0].base) {
		i2c_del_adapter(&smbuses[0].adapter);
		release_region(smbuses[0].base, smbuses[0].size);
	}
	if (smbuses[1].base) {
		i2c_del_adapter(&smbuses[1].adapter);
		release_region(smbuses[1].base, smbuses[1].size);
	}
	kfree(smbuses);
}