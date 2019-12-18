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
struct myrb_hba {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  MYRB_CMD_FLUSH ; 
 int /*<<< orphan*/  myrb_cleanup (struct myrb_hba*) ; 
 int /*<<< orphan*/  myrb_destroy_mempools (struct myrb_hba*) ; 
 int /*<<< orphan*/  myrb_exec_type3 (struct myrb_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct myrb_hba* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void myrb_remove(struct pci_dev *pdev)
{
	struct myrb_hba *cb = pci_get_drvdata(pdev);

	shost_printk(KERN_NOTICE, cb->host, "Flushing Cache...");
	myrb_exec_type3(cb, MYRB_CMD_FLUSH, 0);
	myrb_cleanup(cb);
	myrb_destroy_mempools(cb);
}