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
struct mtk_eth {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_PHY_IAC ; 
 int PHY_IAC_ACCESS ; 
 int PHY_IAC_ADDR_SHIFT ; 
 int PHY_IAC_REG_SHIFT ; 
 int PHY_IAC_START ; 
 int PHY_IAC_WRITE ; 
 scalar_t__ mtk_mdio_busy_wait (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 _mtk_mdio_write(struct mtk_eth *eth, u32 phy_addr,
			   u32 phy_register, u32 write_data)
{
	if (mtk_mdio_busy_wait(eth))
		return -1;

	write_data &= 0xffff;

	mtk_w32(eth, PHY_IAC_ACCESS | PHY_IAC_START | PHY_IAC_WRITE |
		(phy_register << PHY_IAC_REG_SHIFT) |
		(phy_addr << PHY_IAC_ADDR_SHIFT) | write_data,
		MTK_PHY_IAC);

	if (mtk_mdio_busy_wait(eth))
		return -1;

	return 0;
}