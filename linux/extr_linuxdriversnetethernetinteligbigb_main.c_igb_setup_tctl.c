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
struct e1000_hw {int dummy; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_COLLISION_THRESHOLD ; 
 int E1000_CT_SHIFT ; 
 int /*<<< orphan*/  E1000_TCTL ; 
 int E1000_TCTL_CT ; 
 int E1000_TCTL_EN ; 
 int E1000_TCTL_PSP ; 
 int E1000_TCTL_RTLC ; 
 int /*<<< orphan*/  E1000_TXDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_config_collision_dist (struct e1000_hw*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

void igb_setup_tctl(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 tctl;

	/* disable queue 0 which is enabled by default on 82575 and 82576 */
	wr32(E1000_TXDCTL(0), 0);

	/* Program the Transmit Control Register */
	tctl = rd32(E1000_TCTL);
	tctl &= ~E1000_TCTL_CT;
	tctl |= E1000_TCTL_PSP | E1000_TCTL_RTLC |
		(E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT);

	igb_config_collision_dist(hw);

	/* Enable transmits */
	tctl |= E1000_TCTL_EN;

	wr32(E1000_TCTL, tctl);
}