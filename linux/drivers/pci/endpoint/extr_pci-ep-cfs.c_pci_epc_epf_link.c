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
typedef  scalar_t__ u32 ;
struct pci_epf_group {struct pci_epf* epf; } ;
struct pci_epf {scalar_t__ func_no; } ;
struct pci_epc_group {int /*<<< orphan*/  function_num_map; struct pci_epc* epc; } ;
struct pci_epc {int dummy; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 scalar_t__ BITS_PER_LONG ; 
 int EINVAL ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ *,scalar_t__) ; 
 int pci_epc_add_epf (struct pci_epc*,struct pci_epf*) ; 
 int /*<<< orphan*/  pci_epc_remove_epf (struct pci_epc*,struct pci_epf*) ; 
 int pci_epf_bind (struct pci_epf*) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 struct pci_epc_group* to_pci_epc_group (struct config_item*) ; 
 struct pci_epf_group* to_pci_epf_group (struct config_item*) ; 

__attribute__((used)) static int pci_epc_epf_link(struct config_item *epc_item,
			    struct config_item *epf_item)
{
	int ret;
	u32 func_no = 0;
	struct pci_epf_group *epf_group = to_pci_epf_group(epf_item);
	struct pci_epc_group *epc_group = to_pci_epc_group(epc_item);
	struct pci_epc *epc = epc_group->epc;
	struct pci_epf *epf = epf_group->epf;

	func_no = find_first_zero_bit(&epc_group->function_num_map,
				      BITS_PER_LONG);
	if (func_no >= BITS_PER_LONG)
		return -EINVAL;

	set_bit(func_no, &epc_group->function_num_map);
	epf->func_no = func_no;

	ret = pci_epc_add_epf(epc, epf);
	if (ret)
		goto err_add_epf;

	ret = pci_epf_bind(epf);
	if (ret)
		goto err_epf_bind;

	return 0;

err_epf_bind:
	pci_epc_remove_epf(epc, epf);

err_add_epf:
	clear_bit(func_no, &epc_group->function_num_map);

	return ret;
}