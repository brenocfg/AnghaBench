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
struct sock {int dummy; } ;
struct hash_ctx {int /*<<< orphan*/ * result; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 unsigned int crypto_ahash_digestsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_kzfree_s (struct sock*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void hash_free_result(struct sock *sk, struct hash_ctx *ctx)
{
	unsigned ds;

	if (!ctx->result)
		return;

	ds = crypto_ahash_digestsize(crypto_ahash_reqtfm(&ctx->req));

	sock_kzfree_s(sk, ctx->result, ds);
	ctx->result = NULL;
}