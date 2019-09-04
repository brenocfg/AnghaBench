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
struct skcipher_request {int dummy; } ;
struct TYPE_2__ {struct mv_cesa_engine* engine; } ;
struct mv_cesa_skcipher_req {TYPE_1__ base; } ;
struct mv_cesa_engine {int dummy; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ CESA_DMA_REQ ; 
 scalar_t__ mv_cesa_req_get_type (TYPE_1__*) ; 
 int /*<<< orphan*/  mv_cesa_skcipher_dma_prepare (struct skcipher_request*) ; 
 int /*<<< orphan*/  mv_cesa_skcipher_std_prepare (struct skcipher_request*) ; 
 struct skcipher_request* skcipher_request_cast (struct crypto_async_request*) ; 
 struct mv_cesa_skcipher_req* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static inline void mv_cesa_skcipher_prepare(struct crypto_async_request *req,
					    struct mv_cesa_engine *engine)
{
	struct skcipher_request *skreq = skcipher_request_cast(req);
	struct mv_cesa_skcipher_req *creq = skcipher_request_ctx(skreq);
	creq->base.engine = engine;

	if (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ)
		mv_cesa_skcipher_dma_prepare(skreq);
	else
		mv_cesa_skcipher_std_prepare(skreq);
}