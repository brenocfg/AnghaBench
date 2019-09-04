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
struct shash_desc {int /*<<< orphan*/  flags; struct crypto_shash* tfm; } ;
struct crypto_shash {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ahash_request {TYPE_1__ base; } ;

/* Variables and functions */
 struct shash_desc* ahash_request_ctx (struct ahash_request*) ; 
 struct crypto_shash** crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int crypto_shash_init (struct shash_desc*) ; 

__attribute__((used)) static int shash_async_init(struct ahash_request *req)
{
	struct crypto_shash **ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	struct shash_desc *desc = ahash_request_ctx(req);

	desc->tfm = *ctx;
	desc->flags = req->base.flags;

	return crypto_shash_init(desc);
}