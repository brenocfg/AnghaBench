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
struct skcipher_request {int dummy; } ;
struct mv_cesa_skcipher_req {int /*<<< orphan*/  base; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ CESA_DMA_REQ ; 
 int /*<<< orphan*/  mv_cesa_dma_step (int /*<<< orphan*/ *) ; 
 scalar_t__ mv_cesa_req_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv_cesa_skcipher_std_step (struct skcipher_request*) ; 
 struct skcipher_request* skcipher_request_cast (struct crypto_async_request*) ; 
 struct mv_cesa_skcipher_req* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static void mv_cesa_skcipher_step(struct crypto_async_request *req)
{
	struct skcipher_request *skreq = skcipher_request_cast(req);
	struct mv_cesa_skcipher_req *creq = skcipher_request_ctx(skreq);

	if (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ)
		mv_cesa_dma_step(&creq->base);
	else
		mv_cesa_skcipher_std_step(skreq);
}