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
struct pci_dev {struct aer_stats* aer_stats; } ;
struct aer_stats {int /*<<< orphan*/  rootport_total_nonfatal_errs; int /*<<< orphan*/  rootport_total_fatal_errs; int /*<<< orphan*/  rootport_total_cor_errs; } ;
struct aer_err_source {int status; } ;

/* Variables and functions */
 int PCI_ERR_ROOT_COR_RCV ; 
 int PCI_ERR_ROOT_FATAL_RCV ; 
 int PCI_ERR_ROOT_UNCOR_RCV ; 

__attribute__((used)) static void pci_rootport_aer_stats_incr(struct pci_dev *pdev,
				 struct aer_err_source *e_src)
{
	struct aer_stats *aer_stats = pdev->aer_stats;

	if (!aer_stats)
		return;

	if (e_src->status & PCI_ERR_ROOT_COR_RCV)
		aer_stats->rootport_total_cor_errs++;

	if (e_src->status & PCI_ERR_ROOT_UNCOR_RCV) {
		if (e_src->status & PCI_ERR_ROOT_FATAL_RCV)
			aer_stats->rootport_total_fatal_errs++;
		else
			aer_stats->rootport_total_nonfatal_errs++;
	}
}