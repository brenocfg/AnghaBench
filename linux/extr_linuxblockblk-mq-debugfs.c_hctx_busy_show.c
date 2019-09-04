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
struct show_busy_params {struct blk_mq_hw_ctx* hctx; struct seq_file* m; } ;
struct seq_file {int dummy; } ;
struct blk_mq_hw_ctx {TYPE_1__* queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  tag_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct show_busy_params*) ; 
 int /*<<< orphan*/  hctx_show_busy_rq ; 

__attribute__((used)) static int hctx_busy_show(void *data, struct seq_file *m)
{
	struct blk_mq_hw_ctx *hctx = data;
	struct show_busy_params params = { .m = m, .hctx = hctx };

	blk_mq_tagset_busy_iter(hctx->queue->tag_set, hctx_show_busy_rq,
				&params);

	return 0;
}