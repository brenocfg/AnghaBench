#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * result_digest; } ;
struct sha512_hash_ctx {TYPE_1__ job; } ;
struct mcryptd_hash_request_ctx {scalar_t__ out; int /*<<< orphan*/  areq; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 struct sha512_hash_ctx* ahash_request_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sha512_mb_set_results(struct mcryptd_hash_request_ctx *rctx)
{
	int	i;
	struct	sha512_hash_ctx *sctx = ahash_request_ctx(&rctx->areq);
	__be64	*dst = (__be64 *) rctx->out;

	for (i = 0; i < 8; ++i)
		dst[i] = cpu_to_be64(sctx->job.result_digest[i]);

	return 0;
}