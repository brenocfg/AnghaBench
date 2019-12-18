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
typedef  size_t u8 ;
struct link_params {size_t num_phys; TYPE_1__* phy; int /*<<< orphan*/  chip_id; } ;
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdio_ctrl; } ;

/* Variables and functions */
 size_t INT_PHY ; 
 int /*<<< orphan*/  bnx2x_set_mdio_clk (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_set_mdio_emac_per_phy(struct bnx2x *bp,
					struct link_params *params)
{
	u8 phy_index;
	/* Set mdio clock per phy */
	for (phy_index = INT_PHY; phy_index < params->num_phys;
	      phy_index++)
		bnx2x_set_mdio_clk(bp, params->chip_id,
				   params->phy[phy_index].mdio_ctrl);
}