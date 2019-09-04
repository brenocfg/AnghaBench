#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* rar_set ) (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ rar_entry_count; int /*<<< orphan*/  addr; TYPE_3__ ops; } ;
struct TYPE_5__ {int laa_is_present; } ;
struct TYPE_6__ {TYPE_1__ e82571; } ;
struct e1000_hw {TYPE_4__ mac; TYPE_2__ dev_spec; } ;

/* Variables and functions */
 scalar_t__ e1000_82571 ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

void e1000e_set_laa_state_82571(struct e1000_hw *hw, bool state)
{
	if (hw->mac.type != e1000_82571)
		return;

	hw->dev_spec.e82571.laa_is_present = state;

	/* If workaround is activated... */
	if (state)
		/* Hold a copy of the LAA in RAR[14] This is done so that
		 * between the time RAR[0] gets clobbered and the time it
		 * gets fixed, the actual LAA is in one of the RARs and no
		 * incoming packets directed to this port are dropped.
		 * Eventually the LAA will be in RAR[0] and RAR[14].
		 */
		hw->mac.ops.rar_set(hw, hw->mac.addr,
				    hw->mac.rar_entry_count - 1);
}