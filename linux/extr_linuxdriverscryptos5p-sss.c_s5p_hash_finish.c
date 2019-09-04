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
struct s5p_hash_reqctx {scalar_t__ digcnt; struct s5p_aes_dev* dd; } ;
struct s5p_aes_dev {int /*<<< orphan*/  dev; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct s5p_hash_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  s5p_hash_copy_result (struct ahash_request*) ; 

__attribute__((used)) static void s5p_hash_finish(struct ahash_request *req)
{
	struct s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	struct s5p_aes_dev *dd = ctx->dd;

	if (ctx->digcnt)
		s5p_hash_copy_result(req);

	dev_dbg(dd->dev, "hash_finish digcnt: %lld\n", ctx->digcnt);
}