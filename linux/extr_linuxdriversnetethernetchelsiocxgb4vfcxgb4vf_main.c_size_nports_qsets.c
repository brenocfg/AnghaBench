#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vf_resources {unsigned int nvi; int niqflint; unsigned int nethctrl; unsigned int neq; int /*<<< orphan*/  pmask; } ;
struct TYPE_4__ {unsigned int max_ethqsets; } ;
struct TYPE_3__ {unsigned int nports; struct vf_resources vfres; } ;
struct adapter {TYPE_2__ sge; TYPE_1__ params; int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 unsigned int MAX_ETH_QSETS ; 
 unsigned int MAX_NPORTS ; 
 scalar_t__ MSI_MSI ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,...) ; 
 unsigned int hweight32 (int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 scalar_t__ msi ; 

__attribute__((used)) static void size_nports_qsets(struct adapter *adapter)
{
	struct vf_resources *vfres = &adapter->params.vfres;
	unsigned int ethqsets, pmask_nports;

	/* The number of "ports" which we support is equal to the number of
	 * Virtual Interfaces with which we've been provisioned.
	 */
	adapter->params.nports = vfres->nvi;
	if (adapter->params.nports > MAX_NPORTS) {
		dev_warn(adapter->pdev_dev, "only using %d of %d maximum"
			 " allowed virtual interfaces\n", MAX_NPORTS,
			 adapter->params.nports);
		adapter->params.nports = MAX_NPORTS;
	}

	/* We may have been provisioned with more VIs than the number of
	 * ports we're allowed to access (our Port Access Rights Mask).
	 * This is obviously a configuration conflict but we don't want to
	 * crash the kernel or anything silly just because of that.
	 */
	pmask_nports = hweight32(adapter->params.vfres.pmask);
	if (pmask_nports < adapter->params.nports) {
		dev_warn(adapter->pdev_dev, "only using %d of %d provisioned"
			 " virtual interfaces; limited by Port Access Rights"
			 " mask %#x\n", pmask_nports, adapter->params.nports,
			 adapter->params.vfres.pmask);
		adapter->params.nports = pmask_nports;
	}

	/* We need to reserve an Ingress Queue for the Asynchronous Firmware
	 * Event Queue.  And if we're using MSI Interrupts, we'll also need to
	 * reserve an Ingress Queue for a Forwarded Interrupts.
	 *
	 * The rest of the FL/Intr-capable ingress queues will be matched up
	 * one-for-one with Ethernet/Control egress queues in order to form
	 * "Queue Sets" which will be aportioned between the "ports".  For
	 * each Queue Set, we'll need the ability to allocate two Egress
	 * Contexts -- one for the Ingress Queue Free List and one for the TX
	 * Ethernet Queue.
	 *
	 * Note that even if we're currently configured to use MSI-X
	 * Interrupts (module variable msi == MSI_MSIX) we may get downgraded
	 * to MSI Interrupts if we can't get enough MSI-X Interrupts.  If that
	 * happens we'll need to adjust things later.
	 */
	ethqsets = vfres->niqflint - 1 - (msi == MSI_MSI);
	if (vfres->nethctrl != ethqsets)
		ethqsets = min(vfres->nethctrl, ethqsets);
	if (vfres->neq < ethqsets*2)
		ethqsets = vfres->neq/2;
	if (ethqsets > MAX_ETH_QSETS)
		ethqsets = MAX_ETH_QSETS;
	adapter->sge.max_ethqsets = ethqsets;

	if (adapter->sge.max_ethqsets < adapter->params.nports) {
		dev_warn(adapter->pdev_dev, "only using %d of %d available"
			 " virtual interfaces (too few Queue Sets)\n",
			 adapter->sge.max_ethqsets, adapter->params.nports);
		adapter->params.nports = adapter->sge.max_ethqsets;
	}
}