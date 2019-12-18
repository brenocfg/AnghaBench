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
struct pci_epf_test {scalar_t__* reg; int /*<<< orphan*/  cmd_handler; } ;
struct pci_epf_bar {int dummy; } ;
struct pci_epf {int /*<<< orphan*/  func_no; struct pci_epf_bar* bar; struct pci_epc* epc; } ;
struct pci_epc {int dummy; } ;

/* Variables and functions */
 int BAR_0 ; 
 int BAR_5 ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 struct pci_epf_test* epf_get_drvdata (struct pci_epf*) ; 
 int /*<<< orphan*/  pci_epc_clear_bar (struct pci_epc*,int /*<<< orphan*/ ,struct pci_epf_bar*) ; 
 int /*<<< orphan*/  pci_epc_stop (struct pci_epc*) ; 
 int /*<<< orphan*/  pci_epf_free_space (struct pci_epf*,scalar_t__,int) ; 

__attribute__((used)) static void pci_epf_test_unbind(struct pci_epf *epf)
{
	struct pci_epf_test *epf_test = epf_get_drvdata(epf);
	struct pci_epc *epc = epf->epc;
	struct pci_epf_bar *epf_bar;
	int bar;

	cancel_delayed_work(&epf_test->cmd_handler);
	pci_epc_stop(epc);
	for (bar = BAR_0; bar <= BAR_5; bar++) {
		epf_bar = &epf->bar[bar];

		if (epf_test->reg[bar]) {
			pci_epc_clear_bar(epc, epf->func_no, epf_bar);
			pci_epf_free_space(epf, epf_test->reg[bar], bar);
		}
	}
}