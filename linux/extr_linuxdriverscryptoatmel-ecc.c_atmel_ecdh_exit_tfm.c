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
struct atmel_ecdh_ctx {int /*<<< orphan*/  client; int /*<<< orphan*/  fallback; int /*<<< orphan*/  public_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_ecc_i2c_client_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_kpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct atmel_ecdh_ctx* kpp_tfm_ctx (struct crypto_kpp*) ; 

__attribute__((used)) static void atmel_ecdh_exit_tfm(struct crypto_kpp *tfm)
{
	struct atmel_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);

	kfree(ctx->public_key);
	crypto_free_kpp(ctx->fallback);
	atmel_ecc_i2c_client_free(ctx->client);
}