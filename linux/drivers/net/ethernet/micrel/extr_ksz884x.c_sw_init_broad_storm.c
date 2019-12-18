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
struct ksz_hw {TYPE_1__* ksz_switch; } ;
struct TYPE_2__ {int broad_per; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS8842_SWITCH_CTRL_2_OFFSET ; 
 int /*<<< orphan*/  MULTICAST_STORM_DISABLE ; 
 int TOTAL_PORT_NUM ; 
 int /*<<< orphan*/  sw_cfg (struct ksz_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sw_cfg_broad_storm (struct ksz_hw*,int) ; 
 int /*<<< orphan*/  sw_dis_broad_storm (struct ksz_hw*,int) ; 

__attribute__((used)) static void sw_init_broad_storm(struct ksz_hw *hw)
{
	int port;

	hw->ksz_switch->broad_per = 1;
	sw_cfg_broad_storm(hw, hw->ksz_switch->broad_per);
	for (port = 0; port < TOTAL_PORT_NUM; port++)
		sw_dis_broad_storm(hw, port);
	sw_cfg(hw, KS8842_SWITCH_CTRL_2_OFFSET, MULTICAST_STORM_DISABLE, 1);
}