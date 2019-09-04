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
typedef  int /*<<< orphan*/  u8 ;
struct nitrox_kcrypt_request {int dummy; } ;
struct TYPE_2__ {uintptr_t ctx_handle; } ;
struct nitrox_crypto_ctx {TYPE_1__ u; struct crypto_ctx_hdr* chdr; int /*<<< orphan*/  ndev; } ;
struct ctx_hdr {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_ctx_hdr {scalar_t__ vaddr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct crypto_ctx_hdr* crypto_alloc_context (int /*<<< orphan*/ ) ; 
 struct nitrox_crypto_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 scalar_t__ crypto_skcipher_reqsize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_reqsize (struct crypto_skcipher*,scalar_t__) ; 
 int /*<<< orphan*/  nitrox_get_first_device () ; 
 int /*<<< orphan*/  nitrox_put_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nitrox_skcipher_init(struct crypto_skcipher *tfm)
{
	struct nitrox_crypto_ctx *nctx = crypto_skcipher_ctx(tfm);
	struct crypto_ctx_hdr *chdr;

	/* get the first device */
	nctx->ndev = nitrox_get_first_device();
	if (!nctx->ndev)
		return -ENODEV;

	/* allocate nitrox crypto context */
	chdr = crypto_alloc_context(nctx->ndev);
	if (!chdr) {
		nitrox_put_device(nctx->ndev);
		return -ENOMEM;
	}
	nctx->chdr = chdr;
	nctx->u.ctx_handle = (uintptr_t)((u8 *)chdr->vaddr +
					 sizeof(struct ctx_hdr));
	crypto_skcipher_set_reqsize(tfm, crypto_skcipher_reqsize(tfm) +
				    sizeof(struct nitrox_kcrypt_request));
	return 0;
}