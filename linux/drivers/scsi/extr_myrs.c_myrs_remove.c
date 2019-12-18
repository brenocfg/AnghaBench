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
struct myrs_hba {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  myrs_cleanup (struct myrs_hba*) ; 
 int /*<<< orphan*/  myrs_destroy_mempools (struct myrs_hba*) ; 
 int /*<<< orphan*/  myrs_flush_cache (struct myrs_hba*) ; 
 struct myrs_hba* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void myrs_remove(struct pci_dev *pdev)
{
	struct myrs_hba *cs = pci_get_drvdata(pdev);

	if (cs == NULL)
		return;

	shost_printk(KERN_NOTICE, cs->host, "Flushing Cache...");
	myrs_flush_cache(cs);
	myrs_destroy_mempools(cs);
	myrs_cleanup(cs);
}