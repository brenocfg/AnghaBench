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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct i3c_master_controller {TYPE_2__* ops; TYPE_1__ bus; scalar_t__ init_done; } ;
struct i3c_ccc_cmd {int id; scalar_t__ err; int /*<<< orphan*/  ndests; int /*<<< orphan*/  dests; } ;
struct TYPE_4__ {int (* send_ccc_cmd ) (struct i3c_master_controller*,struct i3c_ccc_cmd*) ;int /*<<< orphan*/  (* supports_ccc_cmd ) (struct i3c_master_controller*,struct i3c_ccc_cmd*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int I3C_CCC_DIRECT ; 
 scalar_t__ I3C_ERROR_UNKNOWN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct i3c_master_controller*,struct i3c_ccc_cmd*) ; 
 int stub2 (struct i3c_master_controller*,struct i3c_ccc_cmd*) ; 

__attribute__((used)) static int i3c_master_send_ccc_cmd_locked(struct i3c_master_controller *master,
					  struct i3c_ccc_cmd *cmd)
{
	int ret;

	if (!cmd || !master)
		return -EINVAL;

	if (WARN_ON(master->init_done &&
		    !rwsem_is_locked(&master->bus.lock)))
		return -EINVAL;

	if (!master->ops->send_ccc_cmd)
		return -ENOTSUPP;

	if ((cmd->id & I3C_CCC_DIRECT) && (!cmd->dests || !cmd->ndests))
		return -EINVAL;

	if (master->ops->supports_ccc_cmd &&
	    !master->ops->supports_ccc_cmd(master, cmd))
		return -ENOTSUPP;

	ret = master->ops->send_ccc_cmd(master, cmd);
	if (ret) {
		if (cmd->err != I3C_ERROR_UNKNOWN)
			return cmd->err;

		return ret;
	}

	return 0;
}