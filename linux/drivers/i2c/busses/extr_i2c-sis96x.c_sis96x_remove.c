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

/* Variables and functions */
 int /*<<< orphan*/  SMB_IOSIZE ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis96x_adapter ; 
 scalar_t__ sis96x_smbus_base ; 

__attribute__((used)) static void sis96x_remove(struct pci_dev *dev)
{
	if (sis96x_smbus_base) {
		i2c_del_adapter(&sis96x_adapter);
		release_region(sis96x_smbus_base, SMB_IOSIZE);
		sis96x_smbus_base = 0;
	}
}