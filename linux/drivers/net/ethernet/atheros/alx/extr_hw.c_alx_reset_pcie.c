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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct alx_hw {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_MASTER ; 
 int ALX_MASTER_PCLKSEL_SRDS ; 
 int ALX_MASTER_WAKEN_25M ; 
 int ALX_PCI_CMD ; 
 int /*<<< orphan*/  ALX_PDLL_TRNS1 ; 
 int ALX_PDLL_TRNS1_D3PLLOFF_EN ; 
 int /*<<< orphan*/  ALX_UE_SVRT ; 
 int ALX_UE_SVRT_DLPROTERR ; 
 int ALX_UE_SVRT_FCPROTERR ; 
 int /*<<< orphan*/  ALX_WOL0 ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_INTX_DISABLE ; 
 int /*<<< orphan*/  alx_enable_aspm (struct alx_hw*,int,int) ; 
 int /*<<< orphan*/  alx_hw_revision (struct alx_hw*) ; 
 scalar_t__ alx_hw_with_cr (struct alx_hw*) ; 
 scalar_t__ alx_is_rev_a (int /*<<< orphan*/ ) ; 
 int alx_read_mem32 (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void alx_reset_pcie(struct alx_hw *hw)
{
	u8 rev = alx_hw_revision(hw);
	u32 val;
	u16 val16;

	/* Workaround for PCI problem when BIOS sets MMRBC incorrectly. */
	pci_read_config_word(hw->pdev, PCI_COMMAND, &val16);
	if (!(val16 & ALX_PCI_CMD) || (val16 & PCI_COMMAND_INTX_DISABLE)) {
		val16 = (val16 | ALX_PCI_CMD) & ~PCI_COMMAND_INTX_DISABLE;
		pci_write_config_word(hw->pdev, PCI_COMMAND, val16);
	}

	/* clear WoL setting/status */
	val = alx_read_mem32(hw, ALX_WOL0);
	alx_write_mem32(hw, ALX_WOL0, 0);

	val = alx_read_mem32(hw, ALX_PDLL_TRNS1);
	alx_write_mem32(hw, ALX_PDLL_TRNS1, val & ~ALX_PDLL_TRNS1_D3PLLOFF_EN);

	/* mask some pcie error bits */
	val = alx_read_mem32(hw, ALX_UE_SVRT);
	val &= ~(ALX_UE_SVRT_DLPROTERR | ALX_UE_SVRT_FCPROTERR);
	alx_write_mem32(hw, ALX_UE_SVRT, val);

	/* wol 25M & pclk */
	val = alx_read_mem32(hw, ALX_MASTER);
	if (alx_is_rev_a(rev) && alx_hw_with_cr(hw)) {
		if ((val & ALX_MASTER_WAKEN_25M) == 0 ||
		    (val & ALX_MASTER_PCLKSEL_SRDS) == 0)
			alx_write_mem32(hw, ALX_MASTER,
					val | ALX_MASTER_PCLKSEL_SRDS |
					ALX_MASTER_WAKEN_25M);
	} else {
		if ((val & ALX_MASTER_WAKEN_25M) == 0 ||
		    (val & ALX_MASTER_PCLKSEL_SRDS) != 0)
			alx_write_mem32(hw, ALX_MASTER,
					(val & ~ALX_MASTER_PCLKSEL_SRDS) |
					ALX_MASTER_WAKEN_25M);
	}

	/* ASPM setting */
	alx_enable_aspm(hw, true, true);

	udelay(10);
}