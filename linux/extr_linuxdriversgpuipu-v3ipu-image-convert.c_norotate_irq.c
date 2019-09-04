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
struct ipu_image_convert_run {struct ipu_image_convert_ctx* ctx; } ;
struct ipu_image_convert_ctx {int /*<<< orphan*/  rot_mode; } ;
struct ipu_image_convert_chan {int /*<<< orphan*/  irqlock; struct ipu_image_convert_run* current_run; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  do_irq (struct ipu_image_convert_run*) ; 
 scalar_t__ ipu_rot_mode_is_irt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t norotate_irq(int irq, void *data)
{
	struct ipu_image_convert_chan *chan = data;
	struct ipu_image_convert_ctx *ctx;
	struct ipu_image_convert_run *run;
	unsigned long flags;
	irqreturn_t ret;

	spin_lock_irqsave(&chan->irqlock, flags);

	/* get current run and its context */
	run = chan->current_run;
	if (!run) {
		ret = IRQ_NONE;
		goto out;
	}

	ctx = run->ctx;

	if (ipu_rot_mode_is_irt(ctx->rot_mode)) {
		/* this is a rotation operation, just ignore */
		spin_unlock_irqrestore(&chan->irqlock, flags);
		return IRQ_HANDLED;
	}

	ret = do_irq(run);
out:
	spin_unlock_irqrestore(&chan->irqlock, flags);
	return ret;
}