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
struct mv_cesa_req {int /*<<< orphan*/  engine; } ;
struct mv_cesa_ahash_req {struct mv_cesa_req base; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct mv_cesa_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  mv_cesa_dma_prepare (struct mv_cesa_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mv_cesa_ahash_dma_prepare(struct ahash_request *req)
{
	struct mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	struct mv_cesa_req *basereq = &creq->base;

	mv_cesa_dma_prepare(basereq, basereq->engine);
}