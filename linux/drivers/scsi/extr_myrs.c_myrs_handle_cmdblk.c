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
struct myrs_hba {int dummy; } ;
struct myrs_cmdblk {int /*<<< orphan*/ * complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void myrs_handle_cmdblk(struct myrs_hba *cs, struct myrs_cmdblk *cmd_blk)
{
	if (!cmd_blk)
		return;

	if (cmd_blk->complete) {
		complete(cmd_blk->complete);
		cmd_blk->complete = NULL;
	}
}