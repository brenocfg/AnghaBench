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
typedef  union myrb_cmd_mbox {int dummy; } myrb_cmd_mbox ;
struct myrb_cmdblk {scalar_t__ status; union myrb_cmd_mbox mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (union myrb_cmd_mbox*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void myrb_reset_cmd(struct myrb_cmdblk *cmd_blk)
{
	union myrb_cmd_mbox *mbox = &cmd_blk->mbox;

	memset(mbox, 0, sizeof(union myrb_cmd_mbox));
	cmd_blk->status = 0;
}