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
struct shash_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;
struct p8_ghash_desc_ctx {TYPE_1__ fallback_desc; int /*<<< orphan*/  shash; scalar_t__ bytes; } ;
struct p8_ghash_ctx {int /*<<< orphan*/  fallback; } ;

/* Variables and functions */
 int /*<<< orphan*/  GHASH_DIGEST_SIZE ; 
 int crypto_shash_init (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_shash_tfm (int /*<<< orphan*/ ) ; 
 struct p8_ghash_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct p8_ghash_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int p8_ghash_init(struct shash_desc *desc)
{
	struct p8_ghash_ctx *ctx = crypto_tfm_ctx(crypto_shash_tfm(desc->tfm));
	struct p8_ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	dctx->bytes = 0;
	memset(dctx->shash, 0, GHASH_DIGEST_SIZE);
	dctx->fallback_desc.tfm = ctx->fallback;
	dctx->fallback_desc.flags = desc->flags;
	return crypto_shash_init(&dctx->fallback_desc);
}