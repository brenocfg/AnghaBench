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
typedef  int /*<<< orphan*/  uint8_t ;
struct si476x_core {int /*<<< orphan*/  stc; int /*<<< orphan*/  tuning; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI476X_TIMEOUT_TUNE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si476x_cmd_clear_stc (struct si476x_core*) ; 
 int si476x_core_send_command (struct si476x_core*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_killable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si476x_cmd_tune_seek_freq(struct si476x_core *core,
				     uint8_t cmd,
				     const uint8_t args[], size_t argn,
				     uint8_t *resp, size_t respn)
{
	int err;


	atomic_set(&core->stc, 0);
	err = si476x_core_send_command(core, cmd, args, argn, resp, respn,
				       SI476X_TIMEOUT_TUNE);
	if (!err) {
		wait_event_killable(core->tuning,
				    atomic_read(&core->stc));
		si476x_cmd_clear_stc(core);
	}

	return err;
}