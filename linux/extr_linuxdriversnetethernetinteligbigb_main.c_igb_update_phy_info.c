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
struct timer_list {int dummy; } ;
struct igb_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 struct igb_adapter* adapter ; 
 struct igb_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_get_phy_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_info_timer ; 

__attribute__((used)) static void igb_update_phy_info(struct timer_list *t)
{
	struct igb_adapter *adapter = from_timer(adapter, t, phy_info_timer);
	igb_get_phy_info(&adapter->hw);
}