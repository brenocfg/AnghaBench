#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct si476x_rsq_status_args {int primary; int rsqack; int attune; int cancel; int stcack; } ;
struct TYPE_2__ {int func; } ;
struct si476x_core {TYPE_1__ power_up_parameters; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SI476X_FUNC_AM_RECEIVER 129 
#define  SI476X_FUNC_FM_RECEIVER 128 
 int si476x_core_cmd_am_rsq_status (struct si476x_core*,struct si476x_rsq_status_args*,int /*<<< orphan*/ *) ; 
 int si476x_core_cmd_fm_rsq_status (struct si476x_core*,struct si476x_rsq_status_args*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int si476x_cmd_clear_stc(struct si476x_core *core)
{
	int err;
	struct si476x_rsq_status_args args = {
		.primary	= false,
		.rsqack		= false,
		.attune		= false,
		.cancel		= false,
		.stcack		= true,
	};

	switch (core->power_up_parameters.func) {
	case SI476X_FUNC_FM_RECEIVER:
		err = si476x_core_cmd_fm_rsq_status(core, &args, NULL);
		break;
	case SI476X_FUNC_AM_RECEIVER:
		err = si476x_core_cmd_am_rsq_status(core, &args, NULL);
		break;
	default:
		err = -EINVAL;
	}

	return err;
}