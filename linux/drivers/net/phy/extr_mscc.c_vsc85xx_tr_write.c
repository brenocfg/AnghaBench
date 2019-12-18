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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSCC_PHY_TR_CNTL ; 
 int /*<<< orphan*/  MSCC_PHY_TR_LSB ; 
 int /*<<< orphan*/  MSCC_PHY_TR_MSB ; 
 int TR_ADDR (int /*<<< orphan*/ ) ; 
 int TR_WRITE ; 
 int /*<<< orphan*/  __phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vsc85xx_tr_write(struct phy_device *phydev, u16 addr, u32 val)
{
	__phy_write(phydev, MSCC_PHY_TR_MSB, val >> 16);
	__phy_write(phydev, MSCC_PHY_TR_LSB, val & GENMASK(15, 0));
	__phy_write(phydev, MSCC_PHY_TR_CNTL, TR_WRITE | TR_ADDR(addr));
}