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
struct atmel_sha_reqctx {int /*<<< orphan*/  bufcnt; scalar_t__* digcnt; struct atmel_sha_dev* dd; } ;
struct atmel_sha_dev {int /*<<< orphan*/  dev; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  atmel_sha_copy_ready_hash (struct ahash_request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_sha_finish(struct ahash_request *req)
{
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);
	struct atmel_sha_dev *dd = ctx->dd;

	if (ctx->digcnt[0] || ctx->digcnt[1])
		atmel_sha_copy_ready_hash(req);

	dev_dbg(dd->dev, "digcnt: 0x%llx 0x%llx, bufcnt: %zd\n", ctx->digcnt[1],
		ctx->digcnt[0], ctx->bufcnt);

	return 0;
}