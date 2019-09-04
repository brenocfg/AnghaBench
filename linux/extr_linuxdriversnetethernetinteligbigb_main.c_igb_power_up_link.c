#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ media_type; } ;
struct TYPE_7__ {TYPE_1__ phy; } ;
struct igb_adapter {TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  igb_power_up_phy_copper (TYPE_2__*) ; 
 int /*<<< orphan*/  igb_power_up_serdes_link_82575 (TYPE_2__*) ; 
 int /*<<< orphan*/  igb_reset_phy (TYPE_2__*) ; 
 int /*<<< orphan*/  igb_setup_link (TYPE_2__*) ; 

void igb_power_up_link(struct igb_adapter *adapter)
{
	igb_reset_phy(&adapter->hw);

	if (adapter->hw.phy.media_type == e1000_media_type_copper)
		igb_power_up_phy_copper(&adapter->hw);
	else
		igb_power_up_serdes_link_82575(&adapter->hw);

	igb_setup_link(&adapter->hw);
}