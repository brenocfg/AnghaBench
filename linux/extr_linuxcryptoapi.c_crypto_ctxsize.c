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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_type {unsigned int (* ctxsize ) (struct crypto_alg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct crypto_alg {int cra_alignmask; int cra_flags; struct crypto_type* cra_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CRYPTO_ALG_TYPE_CIPHER 129 
#define  CRYPTO_ALG_TYPE_COMPRESS 128 
 int CRYPTO_ALG_TYPE_MASK ; 
 unsigned int crypto_cipher_ctxsize (struct crypto_alg*) ; 
 unsigned int crypto_compress_ctxsize (struct crypto_alg*) ; 
 int crypto_tfm_ctx_alignment () ; 
 unsigned int stub1 (struct crypto_alg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int crypto_ctxsize(struct crypto_alg *alg, u32 type, u32 mask)
{
	const struct crypto_type *type_obj = alg->cra_type;
	unsigned int len;

	len = alg->cra_alignmask & ~(crypto_tfm_ctx_alignment() - 1);
	if (type_obj)
		return len + type_obj->ctxsize(alg, type, mask);

	switch (alg->cra_flags & CRYPTO_ALG_TYPE_MASK) {
	default:
		BUG();

	case CRYPTO_ALG_TYPE_CIPHER:
		len += crypto_cipher_ctxsize(alg);
		break;

	case CRYPTO_ALG_TYPE_COMPRESS:
		len += crypto_compress_ctxsize(alg);
		break;
	}

	return len;
}