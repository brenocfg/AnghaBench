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
struct atl1e_adapter {int /*<<< orphan*/  mdio_lock; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_INT_STATUS ; 
 int /*<<< orphan*/  atl1e_read_phy_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void atl1e_clear_phy_int(struct atl1e_adapter *adapter)
{
	u16 phy_data;

	spin_lock(&adapter->mdio_lock);
	atl1e_read_phy_reg(&adapter->hw, MII_INT_STATUS, &phy_data);
	spin_unlock(&adapter->mdio_lock);
}