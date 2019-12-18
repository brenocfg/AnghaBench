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
struct ipu_image_convert_run {int /*<<< orphan*/  list; int /*<<< orphan*/  status; struct ipu_image_convert_ctx* ctx; } ;
struct ipu_image_convert_ctx {struct ipu_image_convert_chan* chan; } ;
struct ipu_image_convert_chan {int /*<<< orphan*/  irqlock; struct ipu_image_convert_run* current_run; int /*<<< orphan*/  done_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  convert_stop (struct ipu_image_convert_run*) ; 
 int /*<<< orphan*/  empty_done_q (struct ipu_image_convert_chan*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_next (struct ipu_image_convert_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void force_abort(struct ipu_image_convert_ctx *ctx)
{
	struct ipu_image_convert_chan *chan = ctx->chan;
	struct ipu_image_convert_run *run;
	unsigned long flags;

	spin_lock_irqsave(&chan->irqlock, flags);

	run = chan->current_run;
	if (run && run->ctx == ctx) {
		convert_stop(run);
		run->status = -EIO;
		list_add_tail(&run->list, &chan->done_q);
		chan->current_run = NULL;
		run_next(chan);
	}

	spin_unlock_irqrestore(&chan->irqlock, flags);

	empty_done_q(chan);
}