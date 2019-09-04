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
struct atmel_sha_reqctx {int bufcnt; int /*<<< orphan*/  buffer; } ;
struct atmel_sha_dev {int /*<<< orphan*/  req; } ;

/* Variables and functions */
 struct atmel_sha_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_sha_append_sg (struct atmel_sha_reqctx*) ; 
 int /*<<< orphan*/  atmel_sha_fill_padding (struct atmel_sha_reqctx*,int /*<<< orphan*/ ) ; 
 int atmel_sha_xmit_cpu (struct atmel_sha_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int atmel_sha_update_cpu(struct atmel_sha_dev *dd)
{
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(dd->req);
	int bufcnt;

	atmel_sha_append_sg(ctx);
	atmel_sha_fill_padding(ctx, 0);
	bufcnt = ctx->bufcnt;
	ctx->bufcnt = 0;

	return atmel_sha_xmit_cpu(dd, ctx->buffer, bufcnt, 1);
}