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
struct TYPE_3__ {int system; } ;
struct TYPE_4__ {TYPE_1__ param; } ;
struct msb_data {int read_only; TYPE_2__ regs; struct memstick_dev* card; } ;
struct memstick_host {int (* set_param ) (struct memstick_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct memstick_dev {struct memstick_host* host; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 int /*<<< orphan*/  MEMSTICK_INTERFACE ; 
 int /*<<< orphan*/  MEMSTICK_POWER ; 
 int /*<<< orphan*/  MEMSTICK_POWER_OFF ; 
 int /*<<< orphan*/  MEMSTICK_POWER_ON ; 
 int /*<<< orphan*/  MEMSTICK_SERIAL ; 
 int MEMSTICK_SYS_BAMD ; 
 int MEMSTICK_SYS_PAM ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  h_msb_reset ; 
 int /*<<< orphan*/  msb_invalidate_reg_window (struct msb_data*) ; 
 int msb_run_state_machine (struct msb_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msb_switch_to_parallel (struct msb_data*) ; 
 int stub1 (struct memstick_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct memstick_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (struct memstick_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msb_reset(struct msb_data *msb, bool full)
{

	bool was_parallel = msb->regs.param.system & MEMSTICK_SYS_PAM;
	struct memstick_dev *card = msb->card;
	struct memstick_host *host = card->host;
	int error;

	/* Reset the card */
	msb->regs.param.system = MEMSTICK_SYS_BAMD;

	if (full) {
		error =  host->set_param(host,
					MEMSTICK_POWER, MEMSTICK_POWER_OFF);
		if (error)
			goto out_error;

		msb_invalidate_reg_window(msb);

		error = host->set_param(host,
					MEMSTICK_POWER, MEMSTICK_POWER_ON);
		if (error)
			goto out_error;

		error = host->set_param(host,
					MEMSTICK_INTERFACE, MEMSTICK_SERIAL);
		if (error) {
out_error:
			dbg("Failed to reset the host controller");
			msb->read_only = true;
			return -EFAULT;
		}
	}

	error = msb_run_state_machine(msb, h_msb_reset);
	if (error) {
		dbg("Failed to reset the card");
		msb->read_only = true;
		return -ENODEV;
	}

	/* Set parallel mode */
	if (was_parallel)
		msb_switch_to_parallel(msb);
	return 0;
}