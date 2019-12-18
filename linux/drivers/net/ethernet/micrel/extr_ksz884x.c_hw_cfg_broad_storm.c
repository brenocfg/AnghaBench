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
typedef  int u8 ;
struct ksz_hw {TYPE_1__* ksz_switch; } ;
struct TYPE_2__ {int broad_per; } ;

/* Variables and functions */
 int /*<<< orphan*/  sw_cfg_broad_storm (struct ksz_hw*,int) ; 
 int /*<<< orphan*/  sw_get_broad_storm (struct ksz_hw*,int*) ; 

__attribute__((used)) static void hw_cfg_broad_storm(struct ksz_hw *hw, u8 percent)
{
	if (percent > 100)
		percent = 100;

	sw_cfg_broad_storm(hw, percent);
	sw_get_broad_storm(hw, &percent);
	hw->ksz_switch->broad_per = percent;
}