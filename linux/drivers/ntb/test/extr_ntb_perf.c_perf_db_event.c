#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_ctx {TYPE_1__* ntb; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_read (TYPE_1__*) ; 
 int /*<<< orphan*/  ntb_db_vector_mask (TYPE_1__*,int) ; 
 int /*<<< orphan*/  perf_cmd_recv (struct perf_ctx*) ; 

__attribute__((used)) static void perf_db_event(void *ctx, int vec)
{
	struct perf_ctx *perf = ctx;

	dev_dbg(&perf->ntb->dev, "DB vec %d mask %#llx bits %#llx\n", vec,
		ntb_db_vector_mask(perf->ntb, vec), ntb_db_read(perf->ntb));

	/* Just receive all available commands */
	(void)perf_cmd_recv(perf);
}