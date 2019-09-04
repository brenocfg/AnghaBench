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
struct crypto_akcipher {int /*<<< orphan*/  base; } ;
struct ccp_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccp_rsa_free_key_bufs (struct ccp_ctx*) ; 
 struct ccp_ctx* crypto_tfm_ctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccp_rsa_exit_tfm(struct crypto_akcipher *tfm)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(&tfm->base);

	ccp_rsa_free_key_bufs(ctx);
}