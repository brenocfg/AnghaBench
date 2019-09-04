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
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ media_type; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_2__ phy; TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_CTRL_EXT_LINK_MODE_SGMII ; 
 int /*<<< orphan*/  E1000_THSTAT ; 
 scalar_t__ e1000_i350 ; 
 scalar_t__ e1000_media_type_copper ; 
 int rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool igb_thermal_sensor_event(struct e1000_hw *hw, u32 event)
{
	bool ret = false;
	u32 ctrl_ext, thstat;

	/* check for thermal sensor event on i350 copper only */
	if (hw->mac.type == e1000_i350) {
		thstat = rd32(E1000_THSTAT);
		ctrl_ext = rd32(E1000_CTRL_EXT);

		if ((hw->phy.media_type == e1000_media_type_copper) &&
		    !(ctrl_ext & E1000_CTRL_EXT_LINK_MODE_SGMII))
			ret = !!(thstat & event);
	}

	return ret;
}