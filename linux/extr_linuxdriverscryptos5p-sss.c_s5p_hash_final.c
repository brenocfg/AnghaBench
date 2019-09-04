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
struct s5p_hash_reqctx {int finup; scalar_t__ bufcnt; int /*<<< orphan*/  digcnt; scalar_t__ error; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ BUFLEN ; 
 int EINVAL ; 
 struct s5p_hash_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int s5p_hash_enqueue (struct ahash_request*,int) ; 
 int s5p_hash_final_shash (struct ahash_request*) ; 

__attribute__((used)) static int s5p_hash_final(struct ahash_request *req)
{
	struct s5p_hash_reqctx *ctx = ahash_request_ctx(req);

	ctx->finup = true;
	if (ctx->error)
		return -EINVAL; /* uncompleted hash is not needed */

	if (!ctx->digcnt && ctx->bufcnt < BUFLEN)
		return s5p_hash_final_shash(req);

	return s5p_hash_enqueue(req, false); /* HASH_OP_FINAL */
}