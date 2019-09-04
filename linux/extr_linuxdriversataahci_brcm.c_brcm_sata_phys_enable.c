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
struct brcm_ahci_priv {int port_mask; } ;

/* Variables and functions */
 int BIT (int) ; 
 int SATA_TOP_MAX_PHYS ; 
 int /*<<< orphan*/  brcm_sata_phy_enable (struct brcm_ahci_priv*,int) ; 

__attribute__((used)) static void brcm_sata_phys_enable(struct brcm_ahci_priv *priv)
{
	int i;

	for (i = 0; i < SATA_TOP_MAX_PHYS; i++)
		if (priv->port_mask & BIT(i))
			brcm_sata_phy_enable(priv, i);
}