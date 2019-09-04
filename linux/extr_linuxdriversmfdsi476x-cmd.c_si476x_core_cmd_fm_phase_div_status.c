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
struct si476x_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  CMD_FM_PHASE_DIV_STATUS ; 
 int CMD_FM_PHASE_DIV_STATUS_NRESP ; 
 int /*<<< orphan*/  SI476X_DEFAULT_TIMEOUT ; 
 int si476x_core_send_command (struct si476x_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int si476x_core_cmd_fm_phase_div_status(struct si476x_core *core)
{
	int err;
	u8 resp[CMD_FM_PHASE_DIV_STATUS_NRESP];

	err = si476x_core_send_command(core, CMD_FM_PHASE_DIV_STATUS,
				       NULL, 0,
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);

	return (err < 0) ? err : resp[1];
}