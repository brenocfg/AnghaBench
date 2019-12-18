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
struct aer_rpc {struct pci_dev* rpd; } ;
struct aer_err_source {int status; int /*<<< orphan*/  id; } ;
struct aer_err_info {int multi_error_valid; int /*<<< orphan*/  severity; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AER_CORRECTABLE ; 
 int /*<<< orphan*/  AER_FATAL ; 
 int /*<<< orphan*/  AER_NONFATAL ; 
 int /*<<< orphan*/  ERR_COR_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_UNCOR_ID (int /*<<< orphan*/ ) ; 
 int PCI_ERR_ROOT_COR_RCV ; 
 int PCI_ERR_ROOT_FATAL_RCV ; 
 int PCI_ERR_ROOT_MULTI_COR_RCV ; 
 int PCI_ERR_ROOT_MULTI_UNCOR_RCV ; 
 int PCI_ERR_ROOT_UNCOR_RCV ; 
 int /*<<< orphan*/  aer_print_port_info (struct pci_dev*,struct aer_err_info*) ; 
 int /*<<< orphan*/  aer_process_err_devices (struct aer_err_info*) ; 
 scalar_t__ find_source_device (struct pci_dev*,struct aer_err_info*) ; 
 int /*<<< orphan*/  pci_rootport_aer_stats_incr (struct pci_dev*,struct aer_err_source*) ; 

__attribute__((used)) static void aer_isr_one_error(struct aer_rpc *rpc,
		struct aer_err_source *e_src)
{
	struct pci_dev *pdev = rpc->rpd;
	struct aer_err_info e_info;

	pci_rootport_aer_stats_incr(pdev, e_src);

	/*
	 * There is a possibility that both correctable error and
	 * uncorrectable error being logged. Report correctable error first.
	 */
	if (e_src->status & PCI_ERR_ROOT_COR_RCV) {
		e_info.id = ERR_COR_ID(e_src->id);
		e_info.severity = AER_CORRECTABLE;

		if (e_src->status & PCI_ERR_ROOT_MULTI_COR_RCV)
			e_info.multi_error_valid = 1;
		else
			e_info.multi_error_valid = 0;
		aer_print_port_info(pdev, &e_info);

		if (find_source_device(pdev, &e_info))
			aer_process_err_devices(&e_info);
	}

	if (e_src->status & PCI_ERR_ROOT_UNCOR_RCV) {
		e_info.id = ERR_UNCOR_ID(e_src->id);

		if (e_src->status & PCI_ERR_ROOT_FATAL_RCV)
			e_info.severity = AER_FATAL;
		else
			e_info.severity = AER_NONFATAL;

		if (e_src->status & PCI_ERR_ROOT_MULTI_UNCOR_RCV)
			e_info.multi_error_valid = 1;
		else
			e_info.multi_error_valid = 0;

		aer_print_port_info(pdev, &e_info);

		if (find_source_device(pdev, &e_info))
			aer_process_err_devices(&e_info);
	}
}