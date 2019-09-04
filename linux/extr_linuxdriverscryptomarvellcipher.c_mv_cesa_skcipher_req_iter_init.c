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
struct skcipher_request {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  cryptlen; } ;
struct mv_cesa_skcipher_dma_iter {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  mv_cesa_req_dma_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_cesa_sg_dma_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mv_cesa_skcipher_req_iter_init(struct mv_cesa_skcipher_dma_iter *iter,
			       struct skcipher_request *req)
{
	mv_cesa_req_dma_iter_init(&iter->base, req->cryptlen);
	mv_cesa_sg_dma_iter_init(&iter->src, req->src, DMA_TO_DEVICE);
	mv_cesa_sg_dma_iter_init(&iter->dst, req->dst, DMA_FROM_DEVICE);
}