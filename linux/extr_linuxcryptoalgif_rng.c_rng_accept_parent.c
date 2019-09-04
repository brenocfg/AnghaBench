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
struct sock {int /*<<< orphan*/  sk_destruct; } ;
struct rng_ctx {unsigned int len; void* drng; } ;
struct alg_sock {struct rng_ctx* private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 int /*<<< orphan*/  rng_sock_destruct ; 
 struct rng_ctx* sock_kmalloc (struct sock*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rng_accept_parent(void *private, struct sock *sk)
{
	struct rng_ctx *ctx;
	struct alg_sock *ask = alg_sk(sk);
	unsigned int len = sizeof(*ctx);

	ctx = sock_kmalloc(sk, len, GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->len = len;

	/*
	 * No seeding done at that point -- if multiple accepts are
	 * done on one RNG instance, each resulting FD points to the same
	 * state of the RNG.
	 */

	ctx->drng = private;
	ask->private = ctx;
	sk->sk_destruct = rng_sock_destruct;

	return 0;
}