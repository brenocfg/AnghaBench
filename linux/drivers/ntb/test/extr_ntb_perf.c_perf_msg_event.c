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
struct perf_ctx {TYPE_1__* ntb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_msg_read_sts (TYPE_1__*) ; 
 int /*<<< orphan*/  perf_cmd_recv (struct perf_ctx*) ; 

__attribute__((used)) static void perf_msg_event(void *ctx)
{
	struct perf_ctx *perf = ctx;

	dev_dbg(&perf->ntb->dev, "Msg status bits %#llx\n",
		ntb_msg_read_sts(perf->ntb));

	/* Messages are only sent one-by-one */
	(void)perf_cmd_recv(perf);
}