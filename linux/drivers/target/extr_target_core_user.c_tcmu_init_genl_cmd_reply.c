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
struct tcmu_nl_cmd {int cmd; int /*<<< orphan*/  nl_list; int /*<<< orphan*/  complete; struct tcmu_dev* udev; } ;
struct tcmu_dev {scalar_t__ nl_reply_supported; int /*<<< orphan*/  name; struct tcmu_nl_cmd curr_nl_cmd; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int TCMU_CMD_UNSPEC ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tcmu_nl_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcmu_kern_cmd_reply_supported ; 
 scalar_t__ tcmu_netlink_blocked ; 
 int /*<<< orphan*/  tcmu_nl_cmd_list ; 
 int /*<<< orphan*/  tcmu_nl_cmd_mutex ; 

__attribute__((used)) static int tcmu_init_genl_cmd_reply(struct tcmu_dev *udev, int cmd)
{
	struct tcmu_nl_cmd *nl_cmd = &udev->curr_nl_cmd;

	if (!tcmu_kern_cmd_reply_supported)
		return 0;

	if (udev->nl_reply_supported <= 0)
		return 0;

	mutex_lock(&tcmu_nl_cmd_mutex);

	if (tcmu_netlink_blocked) {
		mutex_unlock(&tcmu_nl_cmd_mutex);
		pr_warn("Failing nl cmd %d on %s. Interface is blocked.\n", cmd,
			udev->name);
		return -EAGAIN;
	}

	if (nl_cmd->cmd != TCMU_CMD_UNSPEC) {
		mutex_unlock(&tcmu_nl_cmd_mutex);
		pr_warn("netlink cmd %d already executing on %s\n",
			 nl_cmd->cmd, udev->name);
		return -EBUSY;
	}

	memset(nl_cmd, 0, sizeof(*nl_cmd));
	nl_cmd->cmd = cmd;
	nl_cmd->udev = udev;
	init_completion(&nl_cmd->complete);
	INIT_LIST_HEAD(&nl_cmd->nl_list);

	list_add_tail(&nl_cmd->nl_list, &tcmu_nl_cmd_list);

	mutex_unlock(&tcmu_nl_cmd_mutex);
	return 0;
}