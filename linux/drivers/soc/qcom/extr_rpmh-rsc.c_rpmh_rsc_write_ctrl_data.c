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
struct tcs_request {scalar_t__ num_cmds; scalar_t__ state; int /*<<< orphan*/  cmds; } ;
struct rsc_drv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_RPMH_PAYLOAD ; 
 scalar_t__ RPMH_ACTIVE_ONLY_STATE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int tcs_ctrl_write (struct rsc_drv*,struct tcs_request const*) ; 

int rpmh_rsc_write_ctrl_data(struct rsc_drv *drv, const struct tcs_request *msg)
{
	if (!msg || !msg->cmds || !msg->num_cmds ||
	    msg->num_cmds > MAX_RPMH_PAYLOAD) {
		pr_err("Payload error\n");
		return -EINVAL;
	}

	/* Data sent to this API will not be sent immediately */
	if (msg->state == RPMH_ACTIVE_ONLY_STATE)
		return -EINVAL;

	return tcs_ctrl_write(drv, msg);
}