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
struct myrb_hba {int dummy; } ;
struct myrb_cmdblk {int /*<<< orphan*/ * completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void myrb_handle_cmdblk(struct myrb_hba *cb, struct myrb_cmdblk *cmd_blk)
{
	if (!cmd_blk)
		return;

	if (cmd_blk->completion) {
		complete(cmd_blk->completion);
		cmd_blk->completion = NULL;
	}
}