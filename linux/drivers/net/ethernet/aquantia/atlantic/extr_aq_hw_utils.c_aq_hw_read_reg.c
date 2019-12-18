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
typedef  unsigned int u32 ;
struct aq_hw_s {unsigned int mmio; int /*<<< orphan*/  flags; TYPE_2__* aq_nic_cfg; } ;
struct TYPE_4__ {TYPE_1__* aq_hw_caps; } ;
struct TYPE_3__ {unsigned int hw_alive_check_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_HW_FLAG_ERR_UNPLUG ; 
 int /*<<< orphan*/  aq_utils_obj_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int readl (unsigned int) ; 

u32 aq_hw_read_reg(struct aq_hw_s *hw, u32 reg)
{
	u32 value = readl(hw->mmio + reg);

	if ((~0U) == value &&
	    (~0U) == readl(hw->mmio +
			   hw->aq_nic_cfg->aq_hw_caps->hw_alive_check_addr))
		aq_utils_obj_set(&hw->flags, AQ_HW_FLAG_ERR_UNPLUG);

	return value;
}