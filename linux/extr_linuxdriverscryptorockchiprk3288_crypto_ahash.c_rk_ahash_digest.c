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
struct rk_crypto_info {int (* enqueue ) (struct rk_crypto_info*,TYPE_1__*) ;} ;
struct rk_ahash_ctx {struct rk_crypto_info* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ahash_request {TYPE_1__ base; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 struct rk_ahash_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int stub1 (struct rk_crypto_info*,TYPE_1__*) ; 
 int zero_message_process (struct ahash_request*) ; 

__attribute__((used)) static int rk_ahash_digest(struct ahash_request *req)
{
	struct rk_ahash_ctx *tctx = crypto_tfm_ctx(req->base.tfm);
	struct rk_crypto_info *dev = tctx->dev;

	if (!req->nbytes)
		return zero_message_process(req);
	else
		return dev->enqueue(dev, &req->base);
}