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
struct crypto_kpp {int dummy; } ;
struct atmel_ecdh_ctx {scalar_t__ fallback; } ;

/* Variables and functions */
 unsigned int ATMEL_ECC_PUBKEY_SIZE ; 
 unsigned int crypto_kpp_maxsize (scalar_t__) ; 
 struct atmel_ecdh_ctx* kpp_tfm_ctx (struct crypto_kpp*) ; 

__attribute__((used)) static unsigned int atmel_ecdh_max_size(struct crypto_kpp *tfm)
{
	struct atmel_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);

	if (ctx->fallback)
		return crypto_kpp_maxsize(ctx->fallback);

	/*
	 * The device only supports NIST P256 ECC keys. The public key size will
	 * always be the same. Use a macro for the key size to avoid unnecessary
	 * computations.
	 */
	return ATMEL_ECC_PUBKEY_SIZE;
}