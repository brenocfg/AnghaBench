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
struct TYPE_3__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct atmel_aes_xts_ctx {TYPE_2__ base; } ;
struct atmel_aes_reqctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_aes_xts_start ; 
 struct atmel_aes_xts_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int atmel_aes_xts_cra_init(struct crypto_tfm *tfm)
{
	struct atmel_aes_xts_ctx *ctx = crypto_tfm_ctx(tfm);

	tfm->crt_ablkcipher.reqsize = sizeof(struct atmel_aes_reqctx);
	ctx->base.start = atmel_aes_xts_start;

	return 0;
}