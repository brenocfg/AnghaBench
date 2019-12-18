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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
struct dax_ctx {scalar_t__ status; int /*<<< orphan*/  fail_count; int /*<<< orphan*/  ccb_count; struct dax_ctx* ca_buf; struct dax_ctx* ccb_buf; } ;

/* Variables and functions */
 scalar_t__ CCA_STAT_NOT_COMPLETED ; 
 int DAX_CA_ELEMS ; 
 int /*<<< orphan*/  dax_ccb_wait (struct dax_ctx*,int) ; 
 int /*<<< orphan*/  dax_dbg (char*,int) ; 
 int /*<<< orphan*/  dax_stat_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_unlock_pages (struct dax_ctx*,int,int) ; 
 int /*<<< orphan*/  kfree (struct dax_ctx*) ; 

__attribute__((used)) static int dax_close(struct inode *ino, struct file *f)
{
	struct dax_ctx *ctx = (struct dax_ctx *)f->private_data;
	int i;

	f->private_data = NULL;

	for (i = 0; i < DAX_CA_ELEMS; i++) {
		if (ctx->ca_buf[i].status == CCA_STAT_NOT_COMPLETED) {
			dax_dbg("CCB[%d] not completed", i);
			dax_ccb_wait(ctx, i);
		}
		dax_unlock_pages(ctx, i, 1);
	}

	kfree(ctx->ccb_buf);
	kfree(ctx->ca_buf);
	dax_stat_dbg("CCBs: %d good, %d bad", ctx->ccb_count, ctx->fail_count);
	kfree(ctx);

	return 0;
}