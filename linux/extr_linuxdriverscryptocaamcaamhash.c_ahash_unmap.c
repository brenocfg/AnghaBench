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
struct device {int dummy; } ;
struct caam_hash_state {scalar_t__ buf_dma; } ;
struct ahash_request {int /*<<< orphan*/  src; } ;
struct ahash_edesc {scalar_t__ sec4_sg_bytes; scalar_t__ sec4_sg_dma; scalar_t__ src_nents; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct caam_hash_state* ahash_request_ctx (struct ahash_request*) ; 
 scalar_t__* current_buflen (struct caam_hash_state*) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ahash_unmap(struct device *dev,
			struct ahash_edesc *edesc,
			struct ahash_request *req, int dst_len)
{
	struct caam_hash_state *state = ahash_request_ctx(req);

	if (edesc->src_nents)
		dma_unmap_sg(dev, req->src, edesc->src_nents, DMA_TO_DEVICE);

	if (edesc->sec4_sg_bytes)
		dma_unmap_single(dev, edesc->sec4_sg_dma,
				 edesc->sec4_sg_bytes, DMA_TO_DEVICE);

	if (state->buf_dma) {
		dma_unmap_single(dev, state->buf_dma, *current_buflen(state),
				 DMA_TO_DEVICE);
		state->buf_dma = 0;
	}
}