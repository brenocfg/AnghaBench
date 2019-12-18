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
typedef  int u32 ;
struct atl1c_hw {int dummy; } ;

/* Variables and functions */
 int AT_HW_MAX_IDLE_DELAY ; 
 int /*<<< orphan*/  AT_READ_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_IDLE_STATUS ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static u32 atl1c_wait_until_idle(struct atl1c_hw *hw, u32 modu_ctrl)
{
	int timeout;
	u32 data;

	for (timeout = 0; timeout < AT_HW_MAX_IDLE_DELAY; timeout++) {
		AT_READ_REG(hw, REG_IDLE_STATUS, &data);
		if ((data & modu_ctrl) == 0)
			return 0;
		msleep(1);
	}
	return data;
}