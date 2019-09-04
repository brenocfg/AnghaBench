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
struct TYPE_2__ {int /*<<< orphan*/  broad_per; } ;

/* Variables and functions */
 int /*<<< orphan*/  port_cfg_broad_storm (struct ksz_hw*,int,int) ; 
 int /*<<< orphan*/  sw_cfg_broad_storm (struct ksz_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sw_ena_broad_storm(struct ksz_hw *hw, int port)
{
	sw_cfg_broad_storm(hw, hw->ksz_switch->broad_per);
	port_cfg_broad_storm(hw, port, 1);
}