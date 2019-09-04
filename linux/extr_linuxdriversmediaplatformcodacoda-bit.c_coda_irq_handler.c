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
struct coda_dev {int /*<<< orphan*/  coda_mutex; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  m2m_dev; } ;
struct coda_ctx {int /*<<< orphan*/  completion; TYPE_1__* dev; scalar_t__ aborting; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_REG_BIT_INT_CLEAR ; 
 int /*<<< orphan*/  CODA_REG_BIT_INT_CLEAR_SET ; 
 int /*<<< orphan*/  CODA_REG_BIT_INT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  coda_debug ; 
 scalar_t__ coda_isbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  coda_read (struct coda_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_write (struct coda_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_coda_bit_done (struct coda_ctx*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct coda_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 

irqreturn_t coda_irq_handler(int irq, void *data)
{
	struct coda_dev *dev = data;
	struct coda_ctx *ctx;

	/* read status register to attend the IRQ */
	coda_read(dev, CODA_REG_BIT_INT_STATUS);
	coda_write(dev, CODA_REG_BIT_INT_CLEAR_SET,
		      CODA_REG_BIT_INT_CLEAR);

	ctx = v4l2_m2m_get_curr_priv(dev->m2m_dev);
	if (ctx == NULL) {
		v4l2_err(&dev->v4l2_dev,
			 "Instance released before the end of transaction\n");
		mutex_unlock(&dev->coda_mutex);
		return IRQ_HANDLED;
	}

	trace_coda_bit_done(ctx);

	if (ctx->aborting) {
		v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
			 "task has been aborted\n");
	}

	if (coda_isbusy(ctx->dev)) {
		v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
			 "coda is still busy!!!!\n");
		return IRQ_NONE;
	}

	complete(&ctx->completion);

	return IRQ_HANDLED;
}