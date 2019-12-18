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
typedef  int u16 ;
struct skge_hw {TYPE_1__** dev; int /*<<< orphan*/  phy_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GM_SMI_CTRL ; 
 int GM_SMI_CT_BUSY ; 
 int GM_SMI_CT_PHY_AD (int /*<<< orphan*/ ) ; 
 int GM_SMI_CT_REG_AD (int) ; 
 int /*<<< orphan*/  GM_SMI_DATA ; 
 int PHY_RETRIES ; 
 int gma_read16 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gm_phy_write(struct skge_hw *hw, int port, u16 reg, u16 val)
{
	int i;

	gma_write16(hw, port, GM_SMI_DATA, val);
	gma_write16(hw, port, GM_SMI_CTRL,
			 GM_SMI_CT_PHY_AD(hw->phy_addr) | GM_SMI_CT_REG_AD(reg));
	for (i = 0; i < PHY_RETRIES; i++) {
		udelay(1);

		if (!(gma_read16(hw, port, GM_SMI_CTRL) & GM_SMI_CT_BUSY))
			return 0;
	}

	pr_warn("%s: phy write timeout\n", hw->dev[port]->name);
	return -EIO;
}