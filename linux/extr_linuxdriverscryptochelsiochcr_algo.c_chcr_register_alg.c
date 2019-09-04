#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct crypto_alg {int cra_flags; char* cra_driver_name; int /*<<< orphan*/  cra_init; int /*<<< orphan*/  cra_ctxsize; int /*<<< orphan*/ * cra_exit; int /*<<< orphan*/  cra_alignmask; void* cra_module; void* cra_priority; } ;
struct chcr_context {int dummy; } ;
struct TYPE_9__ {struct crypto_alg base; int /*<<< orphan*/  statesize; } ;
struct ahash_alg {TYPE_2__ halg; int /*<<< orphan*/  init; int /*<<< orphan*/  setkey; int /*<<< orphan*/  import; int /*<<< orphan*/  export; int /*<<< orphan*/  digest; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; } ;
struct ablk_ctx {int dummy; } ;
struct TYPE_8__ {int cra_flags; char* cra_driver_name; void* cra_module; } ;
struct TYPE_13__ {TYPE_1__ base; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; } ;
struct TYPE_12__ {int cra_flags; int cra_ctxsize; char* cra_driver_name; int /*<<< orphan*/ * cra_type; int /*<<< orphan*/  cra_alignmask; void* cra_module; void* cra_priority; } ;
struct TYPE_10__ {struct ahash_alg hash; TYPE_6__ aead; TYPE_5__ crypto; } ;
struct TYPE_11__ {int is_registered; int type; TYPE_3__ alg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 void* CHCR_CRA_PRIORITY ; 
 int const CRYPTO_ALG_ASYNC ; 
 int const CRYPTO_ALG_NEED_FALLBACK ; 
#define  CRYPTO_ALG_TYPE_ABLKCIPHER 130 
#define  CRYPTO_ALG_TYPE_AEAD 129 
#define  CRYPTO_ALG_TYPE_AHASH 128 
 int CRYPTO_ALG_TYPE_HMAC ; 
 int CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  SZ_AHASH_CTX ; 
 int /*<<< orphan*/  SZ_AHASH_H_CTX ; 
 int /*<<< orphan*/  SZ_AHASH_REQ_CTX ; 
 void* THIS_MODULE ; 
 int /*<<< orphan*/  chcr_aead_cra_exit ; 
 int /*<<< orphan*/  chcr_aead_cra_init ; 
 int /*<<< orphan*/  chcr_aead_decrypt ; 
 int /*<<< orphan*/  chcr_aead_encrypt ; 
 int /*<<< orphan*/  chcr_ahash_digest ; 
 int /*<<< orphan*/  chcr_ahash_export ; 
 int /*<<< orphan*/  chcr_ahash_final ; 
 int /*<<< orphan*/  chcr_ahash_finup ; 
 int /*<<< orphan*/  chcr_ahash_import ; 
 int /*<<< orphan*/  chcr_ahash_setkey ; 
 int /*<<< orphan*/  chcr_ahash_update ; 
 int /*<<< orphan*/ * chcr_hmac_cra_exit ; 
 int /*<<< orphan*/  chcr_hmac_cra_init ; 
 int /*<<< orphan*/  chcr_hmac_init ; 
 int /*<<< orphan*/  chcr_sha_cra_init ; 
 int /*<<< orphan*/  chcr_sha_init ; 
 int /*<<< orphan*/  chcr_unregister_alg () ; 
 int /*<<< orphan*/  crypto_ablkcipher_type ; 
 int crypto_register_aead (TYPE_6__*) ; 
 int crypto_register_ahash (struct ahash_alg*) ; 
 int crypto_register_alg (TYPE_5__*) ; 
 TYPE_4__* driver_algs ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 

__attribute__((used)) static int chcr_register_alg(void)
{
	struct crypto_alg ai;
	struct ahash_alg *a_hash;
	int err = 0, i;
	char *name = NULL;

	for (i = 0; i < ARRAY_SIZE(driver_algs); i++) {
		if (driver_algs[i].is_registered)
			continue;
		switch (driver_algs[i].type & CRYPTO_ALG_TYPE_MASK) {
		case CRYPTO_ALG_TYPE_ABLKCIPHER:
			driver_algs[i].alg.crypto.cra_priority =
				CHCR_CRA_PRIORITY;
			driver_algs[i].alg.crypto.cra_module = THIS_MODULE;
			driver_algs[i].alg.crypto.cra_flags =
				CRYPTO_ALG_TYPE_ABLKCIPHER | CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_NEED_FALLBACK;
			driver_algs[i].alg.crypto.cra_ctxsize =
				sizeof(struct chcr_context) +
				sizeof(struct ablk_ctx);
			driver_algs[i].alg.crypto.cra_alignmask = 0;
			driver_algs[i].alg.crypto.cra_type =
				&crypto_ablkcipher_type;
			err = crypto_register_alg(&driver_algs[i].alg.crypto);
			name = driver_algs[i].alg.crypto.cra_driver_name;
			break;
		case CRYPTO_ALG_TYPE_AEAD:
			driver_algs[i].alg.aead.base.cra_flags =
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_NEED_FALLBACK;
			driver_algs[i].alg.aead.encrypt = chcr_aead_encrypt;
			driver_algs[i].alg.aead.decrypt = chcr_aead_decrypt;
			driver_algs[i].alg.aead.init = chcr_aead_cra_init;
			driver_algs[i].alg.aead.exit = chcr_aead_cra_exit;
			driver_algs[i].alg.aead.base.cra_module = THIS_MODULE;
			err = crypto_register_aead(&driver_algs[i].alg.aead);
			name = driver_algs[i].alg.aead.base.cra_driver_name;
			break;
		case CRYPTO_ALG_TYPE_AHASH:
			a_hash = &driver_algs[i].alg.hash;
			a_hash->update = chcr_ahash_update;
			a_hash->final = chcr_ahash_final;
			a_hash->finup = chcr_ahash_finup;
			a_hash->digest = chcr_ahash_digest;
			a_hash->export = chcr_ahash_export;
			a_hash->import = chcr_ahash_import;
			a_hash->halg.statesize = SZ_AHASH_REQ_CTX;
			a_hash->halg.base.cra_priority = CHCR_CRA_PRIORITY;
			a_hash->halg.base.cra_module = THIS_MODULE;
			a_hash->halg.base.cra_flags = CRYPTO_ALG_ASYNC;
			a_hash->halg.base.cra_alignmask = 0;
			a_hash->halg.base.cra_exit = NULL;

			if (driver_algs[i].type == CRYPTO_ALG_TYPE_HMAC) {
				a_hash->halg.base.cra_init = chcr_hmac_cra_init;
				a_hash->halg.base.cra_exit = chcr_hmac_cra_exit;
				a_hash->init = chcr_hmac_init;
				a_hash->setkey = chcr_ahash_setkey;
				a_hash->halg.base.cra_ctxsize = SZ_AHASH_H_CTX;
			} else {
				a_hash->init = chcr_sha_init;
				a_hash->halg.base.cra_ctxsize = SZ_AHASH_CTX;
				a_hash->halg.base.cra_init = chcr_sha_cra_init;
			}
			err = crypto_register_ahash(&driver_algs[i].alg.hash);
			ai = driver_algs[i].alg.hash.halg.base;
			name = ai.cra_driver_name;
			break;
		}
		if (err) {
			pr_err("chcr : %s : Algorithm registration failed\n",
			       name);
			goto register_err;
		} else {
			driver_algs[i].is_registered = 1;
		}
	}
	return 0;

register_err:
	chcr_unregister_alg();
	return err;
}