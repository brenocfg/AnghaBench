#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct e1000_dev_spec_82575 {int sgmii_active; } ;
struct TYPE_2__ {struct e1000_dev_spec_82575 _82575; } ;
struct e1000_hw {TYPE_1__ dev_spec; } ;

/* Variables and functions */

__attribute__((used)) static bool igb_sgmii_active_82575(struct e1000_hw *hw)
{
	struct e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;
	return dev_spec->sgmii_active;
}