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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT803X_DEBUG_REG_5 ; 
 int /*<<< orphan*/  AT803X_DEBUG_TX_CLK_DLY_EN ; 
 int at803x_debug_reg_mask (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at803x_enable_tx_delay(struct phy_device *phydev)
{
	return at803x_debug_reg_mask(phydev, AT803X_DEBUG_REG_5, 0,
				     AT803X_DEBUG_TX_CLK_DLY_EN);
}