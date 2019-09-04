#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_6__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct e1000_phy_info {TYPE_3__ ops; } ;
struct TYPE_4__ {scalar_t__ media_port; int media_changed; } ;
struct TYPE_5__ {TYPE_1__ _82575; } ;
struct e1000_hw {TYPE_2__ dev_spec; struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_M88E1112_PAGE_ADDR ; 
 int /*<<< orphan*/  E1000_M88E1112_STATUS ; 
 int E1000_M88E1112_STATUS_LINK ; 
 scalar_t__ E1000_MEDIA_PORT_COPPER ; 
 scalar_t__ E1000_MEDIA_PORT_OTHER ; 
 int /*<<< orphan*/  igb_check_for_link_82575 (struct e1000_hw*) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 igb_check_for_link_media_swap(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;
	u8 port = 0;

	/* Check the copper medium. */
	ret_val = phy->ops.write_reg(hw, E1000_M88E1112_PAGE_ADDR, 0);
	if (ret_val)
		return ret_val;

	ret_val = phy->ops.read_reg(hw, E1000_M88E1112_STATUS, &data);
	if (ret_val)
		return ret_val;

	if (data & E1000_M88E1112_STATUS_LINK)
		port = E1000_MEDIA_PORT_COPPER;

	/* Check the other medium. */
	ret_val = phy->ops.write_reg(hw, E1000_M88E1112_PAGE_ADDR, 1);
	if (ret_val)
		return ret_val;

	ret_val = phy->ops.read_reg(hw, E1000_M88E1112_STATUS, &data);
	if (ret_val)
		return ret_val;


	if (data & E1000_M88E1112_STATUS_LINK)
		port = E1000_MEDIA_PORT_OTHER;

	/* Determine if a swap needs to happen. */
	if (port && (hw->dev_spec._82575.media_port != port)) {
		hw->dev_spec._82575.media_port = port;
		hw->dev_spec._82575.media_changed = true;
	}

	if (port == E1000_MEDIA_PORT_COPPER) {
		/* reset page to 0 */
		ret_val = phy->ops.write_reg(hw, E1000_M88E1112_PAGE_ADDR, 0);
		if (ret_val)
			return ret_val;
		igb_check_for_link_82575(hw);
	} else {
		igb_check_for_link_82575(hw);
		/* reset page to 0 */
		ret_val = phy->ops.write_reg(hw, E1000_M88E1112_PAGE_ADDR, 0);
		if (ret_val)
			return ret_val;
	}

	return 0;
}