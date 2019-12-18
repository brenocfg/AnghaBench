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
typedef  int u8 ;
struct cyapa {int dummy; } ;
typedef  int /*<<< orphan*/  resp_data ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int PIP_DEEP_SLEEP_STATE_MASK ; 
 int cyapa_i2c_pip_cmd_irq_sync (struct cyapa*,int*,int,int*,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cyapa_sort_pip_deep_sleep_data ; 

int cyapa_pip_deep_sleep(struct cyapa *cyapa, u8 state)
{
	u8 cmd[] = { 0x05, 0x00, 0x00, 0x08};
	u8 resp_data[5];
	int resp_len;
	int error;

	cmd[2] = state & PIP_DEEP_SLEEP_STATE_MASK;
	resp_len = sizeof(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, sizeof(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_pip_deep_sleep_data, false);
	if (error || ((resp_data[3] & PIP_DEEP_SLEEP_STATE_MASK) != state))
		return -EINVAL;

	return 0;
}