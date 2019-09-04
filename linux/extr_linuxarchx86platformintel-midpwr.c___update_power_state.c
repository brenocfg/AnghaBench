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
struct mid_pwr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_CFG ; 
 int EAGAIN ; 
 int mid_pwr_get_state (struct mid_pwr*,int) ; 
 int /*<<< orphan*/  mid_pwr_set_state (struct mid_pwr*,int,int) ; 
 int mid_pwr_wait_for_cmd (struct mid_pwr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __update_power_state(struct mid_pwr *pwr, int reg, int bit, int new)
{
	int curstate;
	u32 power;
	int ret;

	/* Check if the device is already in desired state */
	power = mid_pwr_get_state(pwr, reg);
	curstate = (power >> bit) & 3;
	if (curstate == new)
		return 0;

	/* Update the power state */
	mid_pwr_set_state(pwr, reg, (power & ~(3 << bit)) | (new << bit));

	/* Send command to SCU */
	ret = mid_pwr_wait_for_cmd(pwr, CMD_SET_CFG);
	if (ret)
		return ret;

	/* Check if the device is already in desired state */
	power = mid_pwr_get_state(pwr, reg);
	curstate = (power >> bit) & 3;
	if (curstate != new)
		return -EAGAIN;

	return 0;
}