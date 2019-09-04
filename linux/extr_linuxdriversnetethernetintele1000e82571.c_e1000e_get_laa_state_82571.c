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
struct TYPE_5__ {int laa_is_present; } ;
struct TYPE_6__ {TYPE_2__ e82571; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ dev_spec; TYPE_1__ mac; } ;

/* Variables and functions */
 scalar_t__ e1000_82571 ; 

bool e1000e_get_laa_state_82571(struct e1000_hw *hw)
{
	if (hw->mac.type != e1000_82571)
		return false;

	return hw->dev_spec.e82571.laa_is_present;
}