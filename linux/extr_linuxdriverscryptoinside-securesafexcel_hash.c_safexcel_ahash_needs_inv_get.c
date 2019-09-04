#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct safexcel_ahash_req {int state_sz; int* processed; int* state; } ;
struct TYPE_4__ {TYPE_1__* ctxr; } ;
struct safexcel_ahash_ctx {TYPE_2__ base; } ;
struct ahash_request {int dummy; } ;
struct TYPE_3__ {scalar_t__* data; } ;

/* Variables and functions */
 int EIP197_COUNTER_BLOCK_SIZE ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 struct safexcel_ahash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 

__attribute__((used)) static inline bool safexcel_ahash_needs_inv_get(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	unsigned int state_w_sz = req->state_sz / sizeof(u32);
	u64 processed;
	int i;

	processed = req->processed[0] / EIP197_COUNTER_BLOCK_SIZE;
	processed += (0xffffffff / EIP197_COUNTER_BLOCK_SIZE) * req->processed[1];

	for (i = 0; i < state_w_sz; i++)
		if (ctx->base.ctxr->data[i] != cpu_to_le32(req->state[i]))
			return true;

	if (ctx->base.ctxr->data[state_w_sz] != cpu_to_le32(processed))
		return true;

	return false;
}