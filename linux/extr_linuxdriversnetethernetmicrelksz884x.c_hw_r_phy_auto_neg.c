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
typedef  int /*<<< orphan*/  u16 ;
struct ksz_hw {scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ KS884X_PHY_AUTO_NEG_OFFSET ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 

__attribute__((used)) static inline void hw_r_phy_auto_neg(struct ksz_hw *hw, int phy, u16 *data)
{
	*data = readw(hw->io + phy + KS884X_PHY_AUTO_NEG_OFFSET);
}