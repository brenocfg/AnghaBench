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
struct hash_ctx {unsigned int len; int /*<<< orphan*/  wait; int /*<<< orphan*/  req; scalar_t__ more; int /*<<< orphan*/ * result; } ;
struct crypto_ahash {int dummy; } ;
struct alg_sock {struct hash_ctx* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ahash_request_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (int /*<<< orphan*/ *,struct crypto_ahash*) ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 int crypto_ahash_reqsize (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_init_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int /*<<< orphan*/  hash_sock_destruct ; 
 struct hash_ctx* sock_kmalloc (struct sock*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hash_accept_parent_nokey(void *private, struct sock *sk)
{
	struct crypto_ahash *tfm = private;
	struct alg_sock *ask = alg_sk(sk);
	struct hash_ctx *ctx;
	unsigned int len = sizeof(*ctx) + crypto_ahash_reqsize(tfm);

	ctx = sock_kmalloc(sk, len, GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->result = NULL;
	ctx->len = len;
	ctx->more = 0;
	crypto_init_wait(&ctx->wait);

	ask->private = ctx;

	ahash_request_set_tfm(&ctx->req, tfm);
	ahash_request_set_callback(&ctx->req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_done, &ctx->wait);

	sk->sk_destruct = hash_sock_destruct;

	return 0;
}