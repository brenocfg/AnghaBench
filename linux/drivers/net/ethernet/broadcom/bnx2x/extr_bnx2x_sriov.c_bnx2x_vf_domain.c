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
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct bnx2x {struct pci_dev* pdev; } ;

/* Variables and functions */
 int pci_domain_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_vf_domain(struct bnx2x *bp, int vfid)
{
	struct pci_dev *dev = bp->pdev;

	return pci_domain_nr(dev->bus);
}