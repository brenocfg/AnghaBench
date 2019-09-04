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
typedef  int u16 ;
struct ksz_hw {scalar_t__ io; } ;

/* Variables and functions */
 int KS884X_PHY_1_CTRL_OFFSET ; 
 int PHY_CTRL_INTERVAL ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static void hw_r_phy(struct ksz_hw *hw, int port, u16 reg, u16 *val)
{
	int phy;

	phy = KS884X_PHY_1_CTRL_OFFSET + port * PHY_CTRL_INTERVAL + reg;
	*val = readw(hw->io + phy);
}