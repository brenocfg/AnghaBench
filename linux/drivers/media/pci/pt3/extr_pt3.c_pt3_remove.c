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
struct pt3_board {int /*<<< orphan*/ * regs; int /*<<< orphan*/  pdev; struct pt3_board* i2c_buf; int /*<<< orphan*/  i2c_adap; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int PT3_NUM_FE ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pt3_board*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pt3_board* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pt3_cleanup_adapter (struct pt3_board*,int) ; 

__attribute__((used)) static void pt3_remove(struct pci_dev *pdev)
{
	struct pt3_board *pt3;
	int i;

	pt3 = pci_get_drvdata(pdev);
	for (i = PT3_NUM_FE - 1; i >= 0; i--)
		pt3_cleanup_adapter(pt3, i);
	i2c_del_adapter(&pt3->i2c_adap);
	kfree(pt3->i2c_buf);
	pci_iounmap(pt3->pdev, pt3->regs[0]);
	pci_iounmap(pt3->pdev, pt3->regs[1]);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kfree(pt3);
}