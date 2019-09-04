#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct eeh_pe {int type; int state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_log ) (struct eeh_pe*,int,scalar_t__*,size_t) ;int /*<<< orphan*/  (* configure_bridge ) (struct eeh_pe*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_ENABLE_IO_FOR_LOG ; 
 int EEH_LOG_PERM ; 
 int /*<<< orphan*/  EEH_OPT_THAW_MMIO ; 
 int EEH_PE_CFG_BLOCKED ; 
 int EEH_PE_PHB ; 
 int /*<<< orphan*/  eeh_dump_pe_log ; 
 scalar_t__ eeh_has_flag (int /*<<< orphan*/ ) ; 
 TYPE_1__* eeh_ops ; 
 int /*<<< orphan*/  eeh_pci_enable (struct eeh_pe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeh_pe_restore_bars (struct eeh_pe*) ; 
 int /*<<< orphan*/  eeh_pe_traverse (struct eeh_pe*,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__* pci_regs_buf ; 
 int /*<<< orphan*/  stub1 (struct eeh_pe*) ; 
 int /*<<< orphan*/  stub2 (struct eeh_pe*,int,scalar_t__*,size_t) ; 

void eeh_slot_error_detail(struct eeh_pe *pe, int severity)
{
	size_t loglen = 0;

	/*
	 * When the PHB is fenced or dead, it's pointless to collect
	 * the data from PCI config space because it should return
	 * 0xFF's. For ER, we still retrieve the data from the PCI
	 * config space.
	 *
	 * For pHyp, we have to enable IO for log retrieval. Otherwise,
	 * 0xFF's is always returned from PCI config space.
	 *
	 * When the @severity is EEH_LOG_PERM, the PE is going to be
	 * removed. Prior to that, the drivers for devices included in
	 * the PE will be closed. The drivers rely on working IO path
	 * to bring the devices to quiet state. Otherwise, PCI traffic
	 * from those devices after they are removed is like to cause
	 * another unexpected EEH error.
	 */
	if (!(pe->type & EEH_PE_PHB)) {
		if (eeh_has_flag(EEH_ENABLE_IO_FOR_LOG) ||
		    severity == EEH_LOG_PERM)
			eeh_pci_enable(pe, EEH_OPT_THAW_MMIO);

		/*
		 * The config space of some PCI devices can't be accessed
		 * when their PEs are in frozen state. Otherwise, fenced
		 * PHB might be seen. Those PEs are identified with flag
		 * EEH_PE_CFG_RESTRICTED, indicating EEH_PE_CFG_BLOCKED
		 * is set automatically when the PE is put to EEH_PE_ISOLATED.
		 *
		 * Restoring BARs possibly triggers PCI config access in
		 * (OPAL) firmware and then causes fenced PHB. If the
		 * PCI config is blocked with flag EEH_PE_CFG_BLOCKED, it's
		 * pointless to restore BARs and dump config space.
		 */
		eeh_ops->configure_bridge(pe);
		if (!(pe->state & EEH_PE_CFG_BLOCKED)) {
			eeh_pe_restore_bars(pe);

			pci_regs_buf[0] = 0;
			eeh_pe_traverse(pe, eeh_dump_pe_log, &loglen);
		}
	}

	eeh_ops->get_log(pe, severity, pci_regs_buf, loglen);
}