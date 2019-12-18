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
struct mvumi_hba {int /*<<< orphan*/  cmd_pool; } ;
struct mvumi_cmd {int /*<<< orphan*/  queue_pointer; int /*<<< orphan*/ * scmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mvumi_return_cmd(struct mvumi_hba *mhba,
						struct mvumi_cmd *cmd)
{
	cmd->scmd = NULL;
	list_add_tail(&cmd->queue_pointer, &mhba->cmd_pool);
}