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
struct device {int dummy; } ;
struct TYPE_2__ {int is_sg_map; } ;
struct chcr_ahash_req_ctx {TYPE_1__ hctx_wr; } ;
struct ahash_request {int /*<<< orphan*/  src; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 struct chcr_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int dma_map_sg (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ ) ; 

int chcr_hash_dma_map(struct device *dev,
		      struct ahash_request *req)
{
	struct chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(req);
	int error = 0;

	if (!req->nbytes)
		return 0;
	error = dma_map_sg(dev, req->src, sg_nents(req->src),
			   DMA_TO_DEVICE);
	if (!error)
		return -ENOMEM;
	req_ctx->hctx_wr.is_sg_map = 1;
	return 0;
}