#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct tool_ctx {int /*<<< orphan*/  msg_wq; TYPE_1__* ntb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_msg_read_sts (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tool_msg_event(void *ctx)
{
	struct tool_ctx *tc = ctx;
	u64 msg_sts;

	msg_sts = ntb_msg_read_sts(tc->ntb);

	dev_dbg(&tc->ntb->dev, "message bits %#llx\n", msg_sts);

	wake_up(&tc->msg_wq);
}