#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ipu_image_convert_run {int /*<<< orphan*/  list; int /*<<< orphan*/  out_phys; int /*<<< orphan*/  in_phys; struct ipu_image_convert_ctx* ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  phys0; } ;
struct TYPE_8__ {TYPE_3__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  phys0; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct ipu_image_convert_ctx {int next_tile; scalar_t__ cur_buf_num; TYPE_4__ out; TYPE_2__ in; struct ipu_image_convert_chan* chan; } ;
struct ipu_image_convert_chan {struct ipu_image_convert_run* current_run; int /*<<< orphan*/  irqlock; } ;

/* Variables and functions */
 int convert_start (struct ipu_image_convert_run*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_run(struct ipu_image_convert_run *run)
{
	struct ipu_image_convert_ctx *ctx = run->ctx;
	struct ipu_image_convert_chan *chan = ctx->chan;

	lockdep_assert_held(&chan->irqlock);

	ctx->in.base.phys0 = run->in_phys;
	ctx->out.base.phys0 = run->out_phys;

	ctx->cur_buf_num = 0;
	ctx->next_tile = 1;

	/* remove run from pending_q and set as current */
	list_del(&run->list);
	chan->current_run = run;

	return convert_start(run, 0);
}