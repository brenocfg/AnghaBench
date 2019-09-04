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
struct hash_ctx {scalar_t__ result; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int crypto_ahash_digestsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ sock_kmalloc (struct sock*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hash_alloc_result(struct sock *sk, struct hash_ctx *ctx)
{
	unsigned ds;

	if (ctx->result)
		return 0;

	ds = crypto_ahash_digestsize(crypto_ahash_reqtfm(&ctx->req));

	ctx->result = sock_kmalloc(sk, ds, GFP_KERNEL);
	if (!ctx->result)
		return -ENOMEM;

	memset(ctx->result, 0, ds);

	return 0;
}