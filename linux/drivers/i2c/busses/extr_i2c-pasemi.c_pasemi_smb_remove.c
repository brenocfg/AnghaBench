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
struct pasemi_smbus {int /*<<< orphan*/  size; int /*<<< orphan*/  base; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pasemi_smbus*) ; 
 struct pasemi_smbus* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pasemi_smb_remove(struct pci_dev *dev)
{
	struct pasemi_smbus *smbus = pci_get_drvdata(dev);

	i2c_del_adapter(&smbus->adapter);
	release_region(smbus->base, smbus->size);
	kfree(smbus);
}