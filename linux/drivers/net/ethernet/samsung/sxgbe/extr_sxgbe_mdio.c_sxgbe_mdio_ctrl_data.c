#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct sxgbe_priv_data {int clk_csr; TYPE_2__* hw; scalar_t__ ioaddr; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ mii; } ;

/* Variables and functions */
 int SXGBE_MII_BUSY ; 
 int SXGBE_SMA_SKIP_ADDRFRM ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sxgbe_mdio_ctrl_data(struct sxgbe_priv_data *sp, u32 cmd,
				 u16 phydata)
{
	u32 reg = phydata;

	reg |= (cmd << 16) | SXGBE_SMA_SKIP_ADDRFRM |
	       ((sp->clk_csr & 0x7) << 19) | SXGBE_MII_BUSY;
	writel(reg, sp->ioaddr + sp->hw->mii.data);
}