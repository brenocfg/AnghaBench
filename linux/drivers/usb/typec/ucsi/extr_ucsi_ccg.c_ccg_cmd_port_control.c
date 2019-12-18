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
struct ucsi_ccg {int port_num; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct ccg_cmd {int data; int len; int delay; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCGX_RAB_PDPORT_ENABLE ; 
 int CMD_SUCCESS ; 
 int PDPORT_1 ; 
 int PDPORT_2 ; 
 int ccg_send_command (struct ucsi_ccg*,struct ccg_cmd*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccg_cmd_port_control(struct ucsi_ccg *uc, bool enable)
{
	struct ccg_cmd cmd;
	int ret;

	cmd.reg = CCGX_RAB_PDPORT_ENABLE;
	if (enable)
		cmd.data = (uc->port_num == 1) ?
			    PDPORT_1 : (PDPORT_1 | PDPORT_2);
	else
		cmd.data = 0x0;
	cmd.len = 1;
	cmd.delay = 10;

	mutex_lock(&uc->lock);

	ret = ccg_send_command(uc, &cmd);

	mutex_unlock(&uc->lock);

	if (ret != CMD_SUCCESS) {
		dev_err(uc->dev, "port control failed ret=%d\n", ret);
		return ret;
	}
	return 0;
}