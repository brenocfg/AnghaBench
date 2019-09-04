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
struct crypto_tfm {scalar_t__ __crt_alg; } ;
struct crypto_spawn {int dummy; } ;
struct crypto_instance {int dummy; } ;
struct crypto_cipher {int dummy; } ;
struct cbcmac_tfm_ctx {struct crypto_cipher* child; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_cipher*) ; 
 int PTR_ERR (struct crypto_cipher*) ; 
 struct crypto_spawn* crypto_instance_ctx (struct crypto_instance*) ; 
 struct crypto_cipher* crypto_spawn_cipher (struct crypto_spawn*) ; 
 struct cbcmac_tfm_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int cbcmac_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_cipher *cipher;
	struct crypto_instance *inst = (void *)tfm->__crt_alg;
	struct crypto_spawn *spawn = crypto_instance_ctx(inst);
	struct cbcmac_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	cipher = crypto_spawn_cipher(spawn);
	if (IS_ERR(cipher))
		return PTR_ERR(cipher);

	ctx->child = cipher;

	return 0;
}