#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* cfg_on_link_up ) (struct e1000_hw*) ;} ;
struct TYPE_4__ {scalar_t__ media_type; TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000e_get_speed_and_duplex_copper (struct e1000_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000e_get_speed_and_duplex_fiber_serdes (struct e1000_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_get_link_up_info_80003es2lan(struct e1000_hw *hw, u16 *speed,
					      u16 *duplex)
{
	s32 ret_val;

	if (hw->phy.media_type == e1000_media_type_copper) {
		ret_val = e1000e_get_speed_and_duplex_copper(hw, speed, duplex);
		hw->phy.ops.cfg_on_link_up(hw);
	} else {
		ret_val = e1000e_get_speed_and_duplex_fiber_serdes(hw,
								   speed,
								   duplex);
	}

	return ret_val;
}