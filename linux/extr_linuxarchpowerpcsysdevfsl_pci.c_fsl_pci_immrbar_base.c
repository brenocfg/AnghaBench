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
typedef  int /*<<< orphan*/  u64 ;
struct pci_controller {int dummy; } ;

/* Variables and functions */

u64 fsl_pci_immrbar_base(struct pci_controller *hose)
{
#ifdef CONFIG_PPC_83xx
	if (is_mpc83xx_pci) {
		struct mpc83xx_pcie_priv *pcie = hose->dn->data;
		struct pex_inbound_window *in;
		int i;

		/* Walk the Root Complex Inbound windows to match IMMR base */
		in = pcie->cfg_type0 + PEX_RC_INWIN_BASE;
		for (i = 0; i < 4; i++) {
			/* not enabled, skip */
			if (!(in_le32(&in[i].ar) & PEX_RCIWARn_EN))
				continue;

			if (get_immrbase() == in_le32(&in[i].tar))
				return (u64)in_le32(&in[i].barh) << 32 |
					    in_le32(&in[i].barl);
		}

		printk(KERN_WARNING "could not find PCI BAR matching IMMR\n");
	}
#endif

#if defined(CONFIG_FSL_SOC_BOOKE) || defined(CONFIG_PPC_86xx)
	if (!is_mpc83xx_pci) {
		u32 base;

		pci_bus_read_config_dword(hose->bus,
			PCI_DEVFN(0, 0), PCI_BASE_ADDRESS_0, &base);

		/*
		 * For PEXCSRBAR, bit 3-0 indicate prefetchable and
		 * address type. So when getting base address, these
		 * bits should be masked
		 */
		base &= PCI_BASE_ADDRESS_MEM_MASK;

		return base;
	}
#endif

	return 0;
}