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
struct bnx2 {int /*<<< orphan*/  pdev; int /*<<< orphan*/  fw_last_msg; int /*<<< orphan*/  wol; } ;
typedef  int pci_power_t ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_BC_STATE_CONDITION ; 
 int /*<<< orphan*/  BNX2_CHIP (struct bnx2*) ; 
 int /*<<< orphan*/  BNX2_CHIP_5709 ; 
 int /*<<< orphan*/  BNX2_CHIP_ID (struct bnx2*) ; 
 int /*<<< orphan*/  BNX2_CHIP_ID_5706_A0 ; 
 int /*<<< orphan*/  BNX2_CHIP_ID_5706_A1 ; 
 int BNX2_CONDITION_PM_STATE_MASK ; 
 int BNX2_CONDITION_PM_STATE_UNPREP ; 
 int /*<<< orphan*/  BNX2_EMAC_MODE ; 
 int BNX2_EMAC_MODE_ACPI_RCVD ; 
 int BNX2_EMAC_MODE_MPKT ; 
 int BNX2_EMAC_MODE_MPKT_RCVD ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_RPM_CONFIG ; 
 int BNX2_RPM_CONFIG_ACPI_ENA ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
#define  PCI_D0 129 
#define  PCI_D3hot 128 
 int /*<<< orphan*/  bnx2_setup_wol (struct bnx2*) ; 
 int bnx2_shmem_rd (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_shmem_wr (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_enable_wake (int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  pci_set_power_state (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnx2_set_power_state(struct bnx2 *bp, pci_power_t state)
{
	switch (state) {
	case PCI_D0: {
		u32 val;

		pci_enable_wake(bp->pdev, PCI_D0, false);
		pci_set_power_state(bp->pdev, PCI_D0);

		val = BNX2_RD(bp, BNX2_EMAC_MODE);
		val |= BNX2_EMAC_MODE_MPKT_RCVD | BNX2_EMAC_MODE_ACPI_RCVD;
		val &= ~BNX2_EMAC_MODE_MPKT;
		BNX2_WR(bp, BNX2_EMAC_MODE, val);

		val = BNX2_RD(bp, BNX2_RPM_CONFIG);
		val &= ~BNX2_RPM_CONFIG_ACPI_ENA;
		BNX2_WR(bp, BNX2_RPM_CONFIG, val);
		break;
	}
	case PCI_D3hot: {
		bnx2_setup_wol(bp);
		pci_wake_from_d3(bp->pdev, bp->wol);
		if ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) ||
		    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A1)) {

			if (bp->wol)
				pci_set_power_state(bp->pdev, PCI_D3hot);
			break;

		}
		if (!bp->fw_last_msg && BNX2_CHIP(bp) == BNX2_CHIP_5709) {
			u32 val;

			/* Tell firmware not to power down the PHY yet,
			 * otherwise the other port may not respond to
			 * MMIO reads.
			 */
			val = bnx2_shmem_rd(bp, BNX2_BC_STATE_CONDITION);
			val &= ~BNX2_CONDITION_PM_STATE_MASK;
			val |= BNX2_CONDITION_PM_STATE_UNPREP;
			bnx2_shmem_wr(bp, BNX2_BC_STATE_CONDITION, val);
		}
		pci_set_power_state(bp->pdev, PCI_D3hot);

		/* No more memory access after this point until
		 * device is brought back to D0.
		 */
		break;
	}
	default:
		return -EINVAL;
	}
	return 0;
}