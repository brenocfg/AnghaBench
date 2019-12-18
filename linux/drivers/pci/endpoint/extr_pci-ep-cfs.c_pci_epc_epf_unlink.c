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
struct pci_epf_group {struct pci_epf* epf; } ;
struct pci_epf {int /*<<< orphan*/  func_no; } ;
struct pci_epc_group {int /*<<< orphan*/  function_num_map; struct pci_epc* epc; int /*<<< orphan*/  start; } ;
struct pci_epc {int dummy; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_epc_remove_epf (struct pci_epc*,struct pci_epf*) ; 
 int /*<<< orphan*/  pci_epf_unbind (struct pci_epf*) ; 
 struct pci_epc_group* to_pci_epc_group (struct config_item*) ; 
 struct pci_epf_group* to_pci_epf_group (struct config_item*) ; 

__attribute__((used)) static void pci_epc_epf_unlink(struct config_item *epc_item,
			       struct config_item *epf_item)
{
	struct pci_epc *epc;
	struct pci_epf *epf;
	struct pci_epf_group *epf_group = to_pci_epf_group(epf_item);
	struct pci_epc_group *epc_group = to_pci_epc_group(epc_item);

	WARN_ON_ONCE(epc_group->start);

	epc = epc_group->epc;
	epf = epf_group->epf;
	clear_bit(epf->func_no, &epc_group->function_num_map);
	pci_epf_unbind(epf);
	pci_epc_remove_epf(epc, epf);
}