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
struct TYPE_3__ {int /*<<< orphan*/  dma; } ;
struct mv_cesa_ahash_req {int /*<<< orphan*/  base; TYPE_1__ req; int /*<<< orphan*/  src_nents; } ;
struct ahash_request {int /*<<< orphan*/  src; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct mv_cesa_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 TYPE_2__* cesa_dev ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_cesa_ahash_dma_free_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv_cesa_dma_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mv_cesa_ahash_dma_cleanup(struct ahash_request *req)
{
	struct mv_cesa_ahash_req *creq = ahash_request_ctx(req);

	dma_unmap_sg(cesa_dev->dev, req->src, creq->src_nents, DMA_TO_DEVICE);
	mv_cesa_ahash_dma_free_cache(&creq->req.dma);
	mv_cesa_dma_cleanup(&creq->base);
}