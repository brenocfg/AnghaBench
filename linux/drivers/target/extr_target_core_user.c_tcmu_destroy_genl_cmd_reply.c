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
struct tcmu_nl_cmd {int /*<<< orphan*/  nl_list; } ;
struct tcmu_dev {scalar_t__ nl_reply_supported; struct tcmu_nl_cmd curr_nl_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tcmu_nl_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcmu_kern_cmd_reply_supported ; 
 int /*<<< orphan*/  tcmu_nl_cmd_mutex ; 

__attribute__((used)) static void tcmu_destroy_genl_cmd_reply(struct tcmu_dev *udev)
{
	struct tcmu_nl_cmd *nl_cmd = &udev->curr_nl_cmd;

	if (!tcmu_kern_cmd_reply_supported)
		return;

	if (udev->nl_reply_supported <= 0)
		return;

	mutex_lock(&tcmu_nl_cmd_mutex);

	list_del(&nl_cmd->nl_list);
	memset(nl_cmd, 0, sizeof(*nl_cmd));

	mutex_unlock(&tcmu_nl_cmd_mutex);
}