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
typedef  scalar_t__ u32 ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int /*<<< orphan*/  netdev; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_LVMMC ; 
 int /*<<< orphan*/  net_ratelimit () ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ rd32 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_check_lvmmc(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 lvmmc;

	lvmmc = rd32(E1000_LVMMC);
	if (lvmmc) {
		if (unlikely(net_ratelimit())) {
			netdev_warn(adapter->netdev,
				    "malformed Tx packet detected and dropped, LVMMC:0x%08x\n",
				    lvmmc);
		}
	}
}