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
typedef  int /*<<< orphan*/  u32 ;
struct e1000_hw {scalar_t__ media_type; int mac_type; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RCTL_LBM_TCVR ; 
 int /*<<< orphan*/  RCTL ; 
#define  e1000_82545 131 
#define  e1000_82545_rev_3 130 
#define  e1000_82546 129 
#define  e1000_82546_rev_3 128 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_media_type_fiber ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 int e1000_set_phy_loopback (struct e1000_adapter*) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e1000_setup_loopback_test(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 rctl;

	if (hw->media_type == e1000_media_type_fiber ||
	    hw->media_type == e1000_media_type_internal_serdes) {
		switch (hw->mac_type) {
		case e1000_82545:
		case e1000_82546:
		case e1000_82545_rev_3:
		case e1000_82546_rev_3:
			return e1000_set_phy_loopback(adapter);
		default:
			rctl = er32(RCTL);
			rctl |= E1000_RCTL_LBM_TCVR;
			ew32(RCTL, rctl);
			return 0;
		}
	} else if (hw->media_type == e1000_media_type_copper) {
		return e1000_set_phy_loopback(adapter);
	}

	return 7;
}