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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F15H_M60H_REPORTED_TEMP_CTRL_OFFSET ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_nb_index_read (struct pci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_tempreg_nb_f15(struct pci_dev *pdev, u32 *regval)
{
	amd_nb_index_read(pdev, PCI_DEVFN(0, 0), 0xb8,
			  F15H_M60H_REPORTED_TEMP_CTRL_OFFSET, regval);
}