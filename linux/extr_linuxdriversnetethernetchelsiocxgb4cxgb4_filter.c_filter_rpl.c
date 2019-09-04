#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ newsmac; } ;
struct filter_entry {unsigned int tid; int valid; scalar_t__ pending; TYPE_2__ fs; struct filter_ctx* ctx; } ;
struct filter_ctx {int result; int tid; int /*<<< orphan*/  completion; } ;
struct cpl_set_tcb_rpl {int /*<<< orphan*/  cookie; } ;
struct TYPE_3__ {unsigned int nftids; unsigned int nsftids; unsigned int ftid_base; struct filter_entry* ftid_tab; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; TYPE_1__ tids; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int FW_FILTER_WR_FLT_ADDED ; 
 unsigned int FW_FILTER_WR_FLT_DELETED ; 
 unsigned int GET_TID (struct cpl_set_tcb_rpl const*) ; 
 unsigned int TCB_COOKIE_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_filter (struct adapter*,struct filter_entry*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int configure_filter_smac (struct adapter*,struct filter_entry*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,unsigned int) ; 

void filter_rpl(struct adapter *adap, const struct cpl_set_tcb_rpl *rpl)
{
	unsigned int tid = GET_TID(rpl);
	struct filter_entry *f = NULL;
	unsigned int max_fidx;
	int idx;

	max_fidx = adap->tids.nftids + adap->tids.nsftids;
	/* Get the corresponding filter entry for this tid */
	if (adap->tids.ftid_tab) {
		/* Check this in normal filter region */
		idx = tid - adap->tids.ftid_base;
		if (idx >= max_fidx)
			return;
		f = &adap->tids.ftid_tab[idx];
		if (f->tid != tid)
			return;
	}

	/* We found the filter entry for this tid */
	if (f) {
		unsigned int ret = TCB_COOKIE_G(rpl->cookie);
		struct filter_ctx *ctx;

		/* Pull off any filter operation context attached to the
		 * filter.
		 */
		ctx = f->ctx;
		f->ctx = NULL;

		if (ret == FW_FILTER_WR_FLT_DELETED) {
			/* Clear the filter when we get confirmation from the
			 * hardware that the filter has been deleted.
			 */
			clear_filter(adap, f);
			if (ctx)
				ctx->result = 0;
		} else if (ret == FW_FILTER_WR_FLT_ADDED) {
			int err = 0;

			if (f->fs.newsmac)
				err = configure_filter_smac(adap, f);

			if (!err) {
				f->pending = 0;  /* async setup completed */
				f->valid = 1;
				if (ctx) {
					ctx->result = 0;
					ctx->tid = idx;
				}
			} else {
				clear_filter(adap, f);
				if (ctx)
					ctx->result = err;
			}
		} else {
			/* Something went wrong.  Issue a warning about the
			 * problem and clear everything out.
			 */
			dev_err(adap->pdev_dev, "filter %u setup failed with error %u\n",
				idx, ret);
			clear_filter(adap, f);
			if (ctx)
				ctx->result = -EINVAL;
		}
		if (ctx)
			complete(&ctx->completion);
	}
}