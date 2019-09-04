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
typedef  int /*<<< orphan*/  u8 ;
struct si476x_power_down_args {int dummy; } ;
struct si476x_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMD_POWER_DOWN ; 
 int CMD_POWER_DOWN_A10_NRESP ; 
 int /*<<< orphan*/  SI476X_DEFAULT_TIMEOUT ; 
 int si476x_core_send_command (struct si476x_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si476x_core_cmd_power_down_a10(struct si476x_core *core,
					  struct si476x_power_down_args *pdargs)
{
	u8 resp[CMD_POWER_DOWN_A10_NRESP];

	return si476x_core_send_command(core, CMD_POWER_DOWN,
					NULL, 0,
					resp, ARRAY_SIZE(resp),
					SI476X_DEFAULT_TIMEOUT);
}