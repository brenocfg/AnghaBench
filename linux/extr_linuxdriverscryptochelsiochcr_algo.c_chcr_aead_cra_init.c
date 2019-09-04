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
struct crypto_aead {int dummy; } ;
struct chcr_aead_reqctx {int dummy; } ;
struct chcr_aead_ctx {int /*<<< orphan*/  sw_cipher; } ;
struct aead_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cra_name; } ;
struct aead_alg {TYPE_1__ base; } ;

/* Variables and functions */
 struct chcr_aead_ctx* AEAD_CTX (int /*<<< orphan*/ ) ; 
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_ctx (struct crypto_aead*) ; 
 int chcr_device_init (int /*<<< orphan*/ ) ; 
 struct aead_alg* crypto_aead_alg (struct crypto_aead*) ; 
 scalar_t__ crypto_aead_reqsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_aead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max (int,scalar_t__) ; 

__attribute__((used)) static int chcr_aead_cra_init(struct crypto_aead *tfm)
{
	struct chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	struct aead_alg *alg = crypto_aead_alg(tfm);

	aeadctx->sw_cipher = crypto_alloc_aead(alg->base.cra_name, 0,
					       CRYPTO_ALG_NEED_FALLBACK |
					       CRYPTO_ALG_ASYNC);
	if  (IS_ERR(aeadctx->sw_cipher))
		return PTR_ERR(aeadctx->sw_cipher);
	crypto_aead_set_reqsize(tfm, max(sizeof(struct chcr_aead_reqctx),
				 sizeof(struct aead_request) +
				 crypto_aead_reqsize(aeadctx->sw_cipher)));
	return chcr_device_init(a_ctx(tfm));
}