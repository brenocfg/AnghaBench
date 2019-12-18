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
 int /*<<< orphan*/  ALI1535_SMB_IOSIZE ; 
 int /*<<< orphan*/  ali1535_adapter ; 
 int /*<<< orphan*/  ali1535_smba ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ali1535_remove(struct pci_dev *dev)
{
	i2c_del_adapter(&ali1535_adapter);
	release_region(ali1535_smba, ALI1535_SMB_IOSIZE);
}