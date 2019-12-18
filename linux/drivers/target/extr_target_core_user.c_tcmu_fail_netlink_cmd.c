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
struct tcmu_nl_cmd {scalar_t__ cmd; int /*<<< orphan*/  complete; int /*<<< orphan*/  nl_list; int /*<<< orphan*/  status; struct tcmu_dev* udev; } ;
struct tcmu_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EINTR ; 
 scalar_t__ TCMU_CMD_UNSPEC ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tcmu_netlink_blocked ; 

__attribute__((used)) static int tcmu_fail_netlink_cmd(struct tcmu_nl_cmd *nl_cmd)
{
	struct tcmu_dev *udev = nl_cmd->udev;

	if (!tcmu_netlink_blocked) {
		pr_err("Could not reset device's netlink interface. Netlink is not blocked.\n");
		return -EBUSY;
	}

	if (nl_cmd->cmd != TCMU_CMD_UNSPEC) {
		pr_debug("Aborting nl cmd %d on %s\n", nl_cmd->cmd, udev->name);
		nl_cmd->status = -EINTR;
		list_del(&nl_cmd->nl_list);
		complete(&nl_cmd->complete);
	}
	return 0;
}