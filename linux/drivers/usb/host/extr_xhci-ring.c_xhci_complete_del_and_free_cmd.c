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
typedef  int /*<<< orphan*/  u32 ;
struct xhci_command {scalar_t__ completion; int /*<<< orphan*/  status; int /*<<< orphan*/  cmd_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct xhci_command*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xhci_complete_del_and_free_cmd(struct xhci_command *cmd, u32 status)
{
	list_del(&cmd->cmd_list);

	if (cmd->completion) {
		cmd->status = status;
		complete(cmd->completion);
	} else {
		kfree(cmd);
	}
}