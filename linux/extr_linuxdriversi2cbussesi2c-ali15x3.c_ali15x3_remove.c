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
 int /*<<< orphan*/  ALI15X3_SMB_IOSIZE ; 
 int /*<<< orphan*/  ali15x3_adapter ; 
 int /*<<< orphan*/  ali15x3_smba ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ali15x3_remove(struct pci_dev *dev)
{
	i2c_del_adapter(&ali15x3_adapter);
	release_region(ali15x3_smba, ALI15X3_SMB_IOSIZE);
}