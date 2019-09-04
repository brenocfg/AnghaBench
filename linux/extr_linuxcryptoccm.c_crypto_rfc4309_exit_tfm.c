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
struct crypto_rfc4309_ctx {int /*<<< orphan*/  child; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 struct crypto_rfc4309_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypto_rfc4309_exit_tfm(struct crypto_aead *tfm)
{
	struct crypto_rfc4309_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_free_aead(ctx->child);
}