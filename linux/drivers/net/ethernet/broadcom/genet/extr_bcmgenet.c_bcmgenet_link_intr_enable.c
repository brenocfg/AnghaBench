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
typedef  int /*<<< orphan*/  u32 ;
struct bcmgenet_priv {scalar_t__ phy_interface; TYPE_1__* hw_params; scalar_t__ ext_phy; scalar_t__ internal_phy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int GENET_HAS_MOCA_LINK_DET ; 
 scalar_t__ GENET_IS_V1 (struct bcmgenet_priv*) ; 
 scalar_t__ GENET_IS_V2 (struct bcmgenet_priv*) ; 
 scalar_t__ GENET_IS_V3 (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  INTRL2_CPU_MASK_CLEAR ; 
 scalar_t__ PHY_INTERFACE_MODE_MOCA ; 
 int /*<<< orphan*/  UMAC_IRQ_LINK_EVENT ; 
 int /*<<< orphan*/  UMAC_IRQ_PHY_DET_R ; 
 int /*<<< orphan*/  bcmgenet_intrl2_0_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcmgenet_link_intr_enable(struct bcmgenet_priv *priv)
{
	u32 int0_enable = 0;

	/* Monitor cable plug/unplugged event for internal PHY, external PHY
	 * and MoCA PHY
	 */
	if (priv->internal_phy) {
		int0_enable |= UMAC_IRQ_LINK_EVENT;
		if (GENET_IS_V1(priv) || GENET_IS_V2(priv) || GENET_IS_V3(priv))
			int0_enable |= UMAC_IRQ_PHY_DET_R;
	} else if (priv->ext_phy) {
		int0_enable |= UMAC_IRQ_LINK_EVENT;
	} else if (priv->phy_interface == PHY_INTERFACE_MODE_MOCA) {
		if (priv->hw_params->flags & GENET_HAS_MOCA_LINK_DET)
			int0_enable |= UMAC_IRQ_LINK_EVENT;
	}
	bcmgenet_intrl2_0_writel(priv, int0_enable, INTRL2_CPU_MASK_CLEAR);
}