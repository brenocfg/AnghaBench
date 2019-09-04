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
struct morus640_glue_ops {int dummy; } ;
struct morus640_ctx {struct morus640_glue_ops const* ops; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 struct morus640_ctx* crypto_aead_ctx (struct crypto_aead*) ; 

void crypto_morus640_glue_init_ops(struct crypto_aead *aead,
				   const struct morus640_glue_ops *ops)
{
	struct morus640_ctx *ctx = crypto_aead_ctx(aead);
	ctx->ops = ops;
}