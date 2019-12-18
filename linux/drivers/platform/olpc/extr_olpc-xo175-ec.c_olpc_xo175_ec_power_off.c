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

/* Variables and functions */
 int /*<<< orphan*/  CMD_POWER_OFF ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  olpc_ec_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void olpc_xo175_ec_power_off(void)
{
	while (1) {
		olpc_ec_cmd(CMD_POWER_OFF, NULL, 0, NULL, 0);
		mdelay(1000);
	}
}