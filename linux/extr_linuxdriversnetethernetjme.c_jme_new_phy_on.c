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
struct jme_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_PHY_PWR ; 
 int /*<<< orphan*/  PCI_PRIV_PE1 ; 
 int PE1_GPREG0_ENBG ; 
 int PE1_GPREG0_PBG ; 
 int PHY_PWR_CLKSEL ; 
 int PHY_PWR_DWN1SEL ; 
 int PHY_PWR_DWN1SW ; 
 int PHY_PWR_DWN2 ; 
 int jread32 (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
jme_new_phy_on(struct jme_adapter *jme)
{
	u32 reg;

	reg = jread32(jme, JME_PHY_PWR);
	reg &= ~(PHY_PWR_DWN1SEL | PHY_PWR_DWN1SW |
		 PHY_PWR_DWN2 | PHY_PWR_CLKSEL);
	jwrite32(jme, JME_PHY_PWR, reg);

	pci_read_config_dword(jme->pdev, PCI_PRIV_PE1, &reg);
	reg &= ~PE1_GPREG0_PBG;
	reg |= PE1_GPREG0_ENBG;
	pci_write_config_dword(jme->pdev, PCI_PRIV_PE1, reg);
}