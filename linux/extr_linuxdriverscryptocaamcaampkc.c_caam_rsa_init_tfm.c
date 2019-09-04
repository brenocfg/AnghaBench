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
struct caam_rsa_ctx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct caam_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int /*<<< orphan*/  caam_jr_alloc () ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int caam_rsa_init_tfm(struct crypto_akcipher *tfm)
{
	struct caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);

	ctx->dev = caam_jr_alloc();

	if (IS_ERR(ctx->dev)) {
		pr_err("Job Ring Device allocation for transform failed\n");
		return PTR_ERR(ctx->dev);
	}

	return 0;
}