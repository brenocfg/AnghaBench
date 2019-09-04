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
typedef  int u32 ;
struct mv_cesa_engine {int /*<<< orphan*/  lock; struct crypto_async_request* req; scalar_t__ regs; } ;
struct mv_cesa_ctx {int dummy; } ;
struct crypto_async_request {int /*<<< orphan*/  tfm; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CESA_SA_FPGA_INT_STATUS ; 
 scalar_t__ CESA_SA_INT_STATUS ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct mv_cesa_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_cesa_complete_req (struct mv_cesa_ctx*,struct crypto_async_request*,int) ; 
 struct crypto_async_request* mv_cesa_engine_dequeue_complete_request (struct mv_cesa_engine*) ; 
 int mv_cesa_get_int_mask (struct mv_cesa_engine*) ; 
 int mv_cesa_int_process (struct mv_cesa_engine*,int) ; 
 int /*<<< orphan*/  mv_cesa_rearm_engine (struct mv_cesa_engine*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mv_cesa_int(int irq, void *priv)
{
	struct mv_cesa_engine *engine = priv;
	struct crypto_async_request *req;
	struct mv_cesa_ctx *ctx;
	u32 status, mask;
	irqreturn_t ret = IRQ_NONE;

	while (true) {
		int res;

		mask = mv_cesa_get_int_mask(engine);
		status = readl(engine->regs + CESA_SA_INT_STATUS);

		if (!(status & mask))
			break;

		/*
		 * TODO: avoid clearing the FPGA_INT_STATUS if this not
		 * relevant on some platforms.
		 */
		writel(~status, engine->regs + CESA_SA_FPGA_INT_STATUS);
		writel(~status, engine->regs + CESA_SA_INT_STATUS);

		/* Process fetched requests */
		res = mv_cesa_int_process(engine, status & mask);
		ret = IRQ_HANDLED;

		spin_lock_bh(&engine->lock);
		req = engine->req;
		if (res != -EINPROGRESS)
			engine->req = NULL;
		spin_unlock_bh(&engine->lock);

		ctx = crypto_tfm_ctx(req->tfm);

		if (res && res != -EINPROGRESS)
			mv_cesa_complete_req(ctx, req, res);

		/* Launch the next pending request */
		mv_cesa_rearm_engine(engine);

		/* Iterate over the complete queue */
		while (true) {
			req = mv_cesa_engine_dequeue_complete_request(engine);
			if (!req)
				break;

			ctx = crypto_tfm_ctx(req->tfm);
			mv_cesa_complete_req(ctx, req, 0);
		}
	}

	return ret;
}