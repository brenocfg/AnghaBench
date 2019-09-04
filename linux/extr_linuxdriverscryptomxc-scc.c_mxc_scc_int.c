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
struct mxc_scc_ctx {int dummy; } ;
struct mxc_scc {struct crypto_async_request* req; scalar_t__ base; } ;
struct crypto_async_request {int /*<<< orphan*/  tfm; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ SCC_SCM_INTR_CTRL ; 
 int /*<<< orphan*/  SCC_SCM_INTR_CTRL_CLR_INTR ; 
 scalar_t__ SCC_SCM_STATUS ; 
 int SCC_SCM_STATUS_BUSY ; 
 struct mxc_scc_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxc_scc_ablkcipher_next (struct mxc_scc_ctx*,struct crypto_async_request*) ; 
 int /*<<< orphan*/  mxc_scc_ablkcipher_req_complete (struct crypto_async_request*,struct mxc_scc_ctx*,int) ; 
 int mxc_scc_get_data (struct mxc_scc_ctx*,struct crypto_async_request*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mxc_scc_int(int irq, void *priv)
{
	struct crypto_async_request *req;
	struct mxc_scc_ctx *ctx;
	struct mxc_scc *scc = priv;
	int status;
	int ret;

	status = readl(scc->base + SCC_SCM_STATUS);

	/* clear interrupt control registers */
	writel(SCC_SCM_INTR_CTRL_CLR_INTR, scc->base + SCC_SCM_INTR_CTRL);

	if (status & SCC_SCM_STATUS_BUSY)
		return IRQ_NONE;

	req = scc->req;
	if (req) {
		ctx = crypto_tfm_ctx(req->tfm);
		ret = mxc_scc_get_data(ctx, req);
		if (ret != -EINPROGRESS)
			mxc_scc_ablkcipher_req_complete(req, ctx, ret);
		else
			mxc_scc_ablkcipher_next(ctx, req);
	}

	return IRQ_HANDLED;
}