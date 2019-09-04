#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct safexcel_crypto_priv {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  control0; int /*<<< orphan*/  control1; } ;
struct safexcel_command_desc {TYPE_1__ control_data; } ;
struct safexcel_ahash_req {int* processed; int* state; int state_sz; int /*<<< orphan*/  digest; scalar_t__ finish; } ;
struct TYPE_6__ {TYPE_2__* ctxr; } ;
struct safexcel_ahash_ctx {int /*<<< orphan*/  opad; TYPE_3__ base; int /*<<< orphan*/  ipad; int /*<<< orphan*/  alg; struct safexcel_crypto_priv* priv; } ;
struct TYPE_5__ {void** data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_MD5 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_SHA1 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_SHA224 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_SHA256 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_SHA384 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_SHA512 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_DIGEST_CNT ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_DIGEST_HMAC ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_DIGEST_PRECOMPUTED ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_NO_FINISH_HASH ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_RESTART_HASH ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_SIZE (int) ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_TYPE_HASH_OUT ; 
 int EIP197_COUNTER_BLOCK_SIZE ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void safexcel_context_control(struct safexcel_ahash_ctx *ctx,
				     struct safexcel_ahash_req *req,
				     struct safexcel_command_desc *cdesc,
				     unsigned int digestsize)
{
	struct safexcel_crypto_priv *priv = ctx->priv;
	int i;

	cdesc->control_data.control0 |= CONTEXT_CONTROL_TYPE_HASH_OUT;
	cdesc->control_data.control0 |= ctx->alg;
	cdesc->control_data.control0 |= req->digest;

	if (req->digest == CONTEXT_CONTROL_DIGEST_PRECOMPUTED) {
		if (req->processed[0] || req->processed[1]) {
			if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_MD5)
				cdesc->control_data.control0 |= CONTEXT_CONTROL_SIZE(5);
			else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA1)
				cdesc->control_data.control0 |= CONTEXT_CONTROL_SIZE(6);
			else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA224 ||
				 ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA256)
				cdesc->control_data.control0 |= CONTEXT_CONTROL_SIZE(9);
			else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA384 ||
				 ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA512)
				cdesc->control_data.control0 |= CONTEXT_CONTROL_SIZE(17);

			cdesc->control_data.control1 |= CONTEXT_CONTROL_DIGEST_CNT;
		} else {
			cdesc->control_data.control0 |= CONTEXT_CONTROL_RESTART_HASH;
		}

		if (!req->finish)
			cdesc->control_data.control0 |= CONTEXT_CONTROL_NO_FINISH_HASH;

		/*
		 * Copy the input digest if needed, and setup the context
		 * fields. Do this now as we need it to setup the first command
		 * descriptor.
		 */
		if (req->processed[0] || req->processed[1]) {
			for (i = 0; i < digestsize / sizeof(u32); i++)
				ctx->base.ctxr->data[i] = cpu_to_le32(req->state[i]);

			if (req->finish) {
				u64 count = req->processed[0] / EIP197_COUNTER_BLOCK_SIZE;
				count += ((0xffffffff / EIP197_COUNTER_BLOCK_SIZE) *
					  req->processed[1]);

				/* This is a haredware limitation, as the
				 * counter must fit into an u32. This represents
				 * a farily big amount of input data, so we
				 * shouldn't see this.
				 */
				if (unlikely(count & 0xffff0000)) {
					dev_warn(priv->dev,
						 "Input data is too big\n");
					return;
				}

				ctx->base.ctxr->data[i] = cpu_to_le32(count);
			}
		}
	} else if (req->digest == CONTEXT_CONTROL_DIGEST_HMAC) {
		cdesc->control_data.control0 |= CONTEXT_CONTROL_SIZE(2 * req->state_sz / sizeof(u32));

		memcpy(ctx->base.ctxr->data, ctx->ipad, req->state_sz);
		memcpy(ctx->base.ctxr->data + req->state_sz / sizeof(u32),
		       ctx->opad, req->state_sz);
	}
}