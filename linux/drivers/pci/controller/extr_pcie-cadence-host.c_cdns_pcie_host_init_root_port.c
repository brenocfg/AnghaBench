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
typedef  int u32 ;
struct cdns_pcie {int dummy; } ;
struct cdns_pcie_rc {int vendor_id; int device_id; struct cdns_pcie pcie; } ;

/* Variables and functions */
 int CDNS_PCIE_LM_BAR_CFG_CTRL_DISABLED ; 
 int /*<<< orphan*/  CDNS_PCIE_LM_RC_BAR_CFG ; 
 int CDNS_PCIE_LM_RC_BAR_CFG_BAR0_CTRL (int) ; 
 int CDNS_PCIE_LM_RC_BAR_CFG_BAR1_CTRL (int) ; 
 int CDNS_PCIE_LM_RC_BAR_CFG_IO_32BITS ; 
 int CDNS_PCIE_LM_RC_BAR_CFG_IO_ENABLE ; 
 int CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_64BITS ; 
 int CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_ENABLE ; 
 int PCI_CLASS_BRIDGE_PCI ; 
 int /*<<< orphan*/  PCI_CLASS_DEVICE ; 
 int /*<<< orphan*/  PCI_CLASS_PROG ; 
 int /*<<< orphan*/  PCI_CLASS_REVISION ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 int /*<<< orphan*/  cdns_pcie_rp_writeb (struct cdns_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_pcie_rp_writew (struct cdns_pcie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdns_pcie_writel (struct cdns_pcie*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cdns_pcie_host_init_root_port(struct cdns_pcie_rc *rc)
{
	struct cdns_pcie *pcie = &rc->pcie;
	u32 value, ctrl;

	/*
	 * Set the root complex BAR configuration register:
	 * - disable both BAR0 and BAR1.
	 * - enable Prefetchable Memory Base and Limit registers in type 1
	 *   config space (64 bits).
	 * - enable IO Base and Limit registers in type 1 config
	 *   space (32 bits).
	 */
	ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_DISABLED;
	value = CDNS_PCIE_LM_RC_BAR_CFG_BAR0_CTRL(ctrl) |
		CDNS_PCIE_LM_RC_BAR_CFG_BAR1_CTRL(ctrl) |
		CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_ENABLE |
		CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_64BITS |
		CDNS_PCIE_LM_RC_BAR_CFG_IO_ENABLE |
		CDNS_PCIE_LM_RC_BAR_CFG_IO_32BITS;
	cdns_pcie_writel(pcie, CDNS_PCIE_LM_RC_BAR_CFG, value);

	/* Set root port configuration space */
	if (rc->vendor_id != 0xffff)
		cdns_pcie_rp_writew(pcie, PCI_VENDOR_ID, rc->vendor_id);
	if (rc->device_id != 0xffff)
		cdns_pcie_rp_writew(pcie, PCI_DEVICE_ID, rc->device_id);

	cdns_pcie_rp_writeb(pcie, PCI_CLASS_REVISION, 0);
	cdns_pcie_rp_writeb(pcie, PCI_CLASS_PROG, 0);
	cdns_pcie_rp_writew(pcie, PCI_CLASS_DEVICE, PCI_CLASS_BRIDGE_PCI);

	return 0;
}