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
typedef  int /*<<< orphan*/  u32 ;
struct skcipher_request {int dummy; } ;
struct mv_cesa_req {int dummy; } ;
struct mv_cesa_skcipher_req {struct mv_cesa_req base; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ CESA_STD_REQ ; 
 int mv_cesa_dma_process (struct mv_cesa_req*,int /*<<< orphan*/ ) ; 
 scalar_t__ mv_cesa_req_get_type (struct mv_cesa_req*) ; 
 int mv_cesa_skcipher_std_process (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 struct skcipher_request* skcipher_request_cast (struct crypto_async_request*) ; 
 struct mv_cesa_skcipher_req* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static int mv_cesa_skcipher_process(struct crypto_async_request *req,
				    u32 status)
{
	struct skcipher_request *skreq = skcipher_request_cast(req);
	struct mv_cesa_skcipher_req *creq = skcipher_request_ctx(skreq);
	struct mv_cesa_req *basereq = &creq->base;

	if (mv_cesa_req_get_type(basereq) == CESA_STD_REQ)
		return mv_cesa_skcipher_std_process(skreq, status);

	return mv_cesa_dma_process(basereq, status);
}