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
struct crypto_akcipher {int dummy; } ;
struct caam_rsa_key {int dummy; } ;
struct caam_rsa_ctx {int /*<<< orphan*/  dev; struct caam_rsa_key key; } ;

/* Variables and functions */
 struct caam_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int /*<<< orphan*/  caam_jr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caam_rsa_free_key (struct caam_rsa_key*) ; 

__attribute__((used)) static void caam_rsa_exit_tfm(struct crypto_akcipher *tfm)
{
	struct caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct caam_rsa_key *key = &ctx->key;

	caam_rsa_free_key(key);
	caam_jr_free(ctx->dev);
}