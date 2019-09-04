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
struct stm32_cryp_reqctx {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * unprepare_request; int /*<<< orphan*/  prepare_request; int /*<<< orphan*/  do_one_request; } ;
struct TYPE_4__ {TYPE_1__ op; } ;
struct stm32_cryp_ctx {TYPE_2__ enginectx; } ;
struct crypto_aead {int reqsize; } ;

/* Variables and functions */
 struct stm32_cryp_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  stm32_cryp_aead_one_req ; 
 int /*<<< orphan*/  stm32_cryp_prepare_aead_req ; 

__attribute__((used)) static int stm32_cryp_aes_aead_init(struct crypto_aead *tfm)
{
	struct stm32_cryp_ctx *ctx = crypto_aead_ctx(tfm);

	tfm->reqsize = sizeof(struct stm32_cryp_reqctx);

	ctx->enginectx.op.do_one_request = stm32_cryp_aead_one_req;
	ctx->enginectx.op.prepare_request = stm32_cryp_prepare_aead_req;
	ctx->enginectx.op.unprepare_request = NULL;

	return 0;
}