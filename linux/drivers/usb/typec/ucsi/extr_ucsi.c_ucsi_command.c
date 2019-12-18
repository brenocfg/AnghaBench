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
struct ucsi_control {int dummy; } ;
struct ucsi {int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  complete; TYPE_1__* ppm; } ;
struct TYPE_2__ {int (* cmd ) (TYPE_1__*,struct ucsi_control*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_PENDING ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  UCSI_TIMEOUT_MS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,struct ucsi_control*) ; 
 int /*<<< orphan*/  trace_ucsi_command (struct ucsi_control*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucsi_command(struct ucsi *ucsi, struct ucsi_control *ctrl)
{
	int ret;

	trace_ucsi_command(ctrl);

	set_bit(COMMAND_PENDING, &ucsi->flags);

	ret = ucsi->ppm->cmd(ucsi->ppm, ctrl);
	if (ret)
		goto err_clear_flag;

	if (!wait_for_completion_timeout(&ucsi->complete,
					 msecs_to_jiffies(UCSI_TIMEOUT_MS))) {
		dev_warn(ucsi->dev, "PPM NOT RESPONDING\n");
		ret = -ETIMEDOUT;
	}

err_clear_flag:
	clear_bit(COMMAND_PENDING, &ucsi->flags);

	return ret;
}