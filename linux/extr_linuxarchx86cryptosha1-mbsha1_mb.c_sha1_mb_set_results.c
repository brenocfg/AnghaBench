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
struct sha1_hash_ctx {TYPE_1__ job; } ;
struct mcryptd_hash_request_ctx {scalar_t__ out; int /*<<< orphan*/  areq; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct sha1_hash_ctx* ahash_request_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sha1_mb_set_results(struct mcryptd_hash_request_ctx *rctx)
{
	int	i;
	struct	sha1_hash_ctx *sctx = ahash_request_ctx(&rctx->areq);
	__be32	*dst = (__be32 *) rctx->out;

	for (i = 0; i < 5; ++i)
		dst[i] = cpu_to_be32(sctx->job.result_digest[i]);

	return 0;
}