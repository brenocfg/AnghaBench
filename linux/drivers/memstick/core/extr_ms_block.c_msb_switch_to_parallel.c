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
struct TYPE_3__ {int /*<<< orphan*/  system; } ;
struct TYPE_4__ {TYPE_1__ param; } ;
struct msb_data {int /*<<< orphan*/  caps; TYPE_2__ regs; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  MEMSTICK_CAP_AUTO_GET_INT ; 
 int /*<<< orphan*/  MEMSTICK_SYS_PAM ; 
 int /*<<< orphan*/  h_msb_parallel_switch ; 
 int /*<<< orphan*/  msb_reset (struct msb_data*,int) ; 
 int msb_run_state_machine (struct msb_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int msb_switch_to_parallel(struct msb_data *msb)
{
	int error;

	error = msb_run_state_machine(msb, h_msb_parallel_switch);
	if (error) {
		pr_err("Switch to parallel failed");
		msb->regs.param.system &= ~MEMSTICK_SYS_PAM;
		msb_reset(msb, true);
		return -EFAULT;
	}

	msb->caps |= MEMSTICK_CAP_AUTO_GET_INT;
	return 0;
}