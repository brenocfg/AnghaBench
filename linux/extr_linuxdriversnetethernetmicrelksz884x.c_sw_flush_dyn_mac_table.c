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
struct ksz_hw {int overrides; } ;

/* Variables and functions */
 int FAST_AGING ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  sw_cfg_fast_aging (struct ksz_hw*,int) ; 

__attribute__((used)) static inline void sw_flush_dyn_mac_table(struct ksz_hw *hw)
{
	if (!(hw->overrides & FAST_AGING)) {
		sw_cfg_fast_aging(hw, 1);
		mdelay(1);
		sw_cfg_fast_aging(hw, 0);
	}
}