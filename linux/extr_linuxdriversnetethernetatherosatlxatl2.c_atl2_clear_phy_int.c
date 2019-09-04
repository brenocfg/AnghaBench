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
struct atl2_adapter {int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl2_read_phy_reg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void atl2_clear_phy_int(struct atl2_adapter *adapter)
{
	u16 phy_data;
	spin_lock(&adapter->stats_lock);
	atl2_read_phy_reg(&adapter->hw, 19, &phy_data);
	spin_unlock(&adapter->stats_lock);
}