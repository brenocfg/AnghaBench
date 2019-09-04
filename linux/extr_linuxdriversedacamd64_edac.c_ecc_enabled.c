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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 scalar_t__ BIT (scalar_t__) ; 
 int /*<<< orphan*/  MSR_IA32_MCG_CTL ; 
 int /*<<< orphan*/  NBCFG ; 
 int NBCFG_ECC_ENABLE ; 
 scalar_t__ NUM_UMCS ; 
 int UMCCH_SDP_CTRL ; 
 int UMCCH_UMC_CAP_HI ; 
 int UMC_ECC_ENABLED ; 
 int UMC_SDP_INIT ; 
 int /*<<< orphan*/  amd64_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  amd64_read_pci_cfg (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ amd_smn_read (int /*<<< orphan*/ ,int,int*) ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  ecc_msg ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int get_umc_base (scalar_t__) ; 
 int nb_mce_bank_enabled_on_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ecc_enabled(struct pci_dev *F3, u16 nid)
{
	bool nb_mce_en = false;
	u8 ecc_en = 0, i;
	u32 value;

	if (boot_cpu_data.x86 >= 0x17) {
		u8 umc_en_mask = 0, ecc_en_mask = 0;

		for (i = 0; i < NUM_UMCS; i++) {
			u32 base = get_umc_base(i);

			/* Only check enabled UMCs. */
			if (amd_smn_read(nid, base + UMCCH_SDP_CTRL, &value))
				continue;

			if (!(value & UMC_SDP_INIT))
				continue;

			umc_en_mask |= BIT(i);

			if (amd_smn_read(nid, base + UMCCH_UMC_CAP_HI, &value))
				continue;

			if (value & UMC_ECC_ENABLED)
				ecc_en_mask |= BIT(i);
		}

		/* Check whether at least one UMC is enabled: */
		if (umc_en_mask)
			ecc_en = umc_en_mask == ecc_en_mask;
		else
			edac_dbg(0, "Node %d: No enabled UMCs.\n", nid);

		/* Assume UMC MCA banks are enabled. */
		nb_mce_en = true;
	} else {
		amd64_read_pci_cfg(F3, NBCFG, &value);

		ecc_en = !!(value & NBCFG_ECC_ENABLE);

		nb_mce_en = nb_mce_bank_enabled_on_node(nid);
		if (!nb_mce_en)
			edac_dbg(0, "NB MCE bank disabled, set MSR 0x%08x[4] on node %d to enable.\n",
				     MSR_IA32_MCG_CTL, nid);
	}

	amd64_info("Node %d: DRAM ECC %s.\n",
		   nid, (ecc_en ? "enabled" : "disabled"));

	if (!ecc_en || !nb_mce_en) {
		amd64_info("%s", ecc_msg);
		return false;
	}
	return true;
}