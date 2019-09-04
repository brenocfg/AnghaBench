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
 int /*<<< orphan*/  amd756_ioport ; 
 int /*<<< orphan*/  amd756_smbus ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amd756_remove(struct pci_dev *dev)
{
	i2c_del_adapter(&amd756_smbus);
	release_region(amd756_ioport, SMB_IOSIZE);
}