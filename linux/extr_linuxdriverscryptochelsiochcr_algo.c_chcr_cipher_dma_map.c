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
struct ablkcipher_request {scalar_t__ src; scalar_t__ dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int dma_map_sg (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (scalar_t__) ; 

int chcr_cipher_dma_map(struct device *dev,
			struct ablkcipher_request *req)
{
	int error;

	if (req->src == req->dst) {
		error = dma_map_sg(dev, req->src, sg_nents(req->src),
				   DMA_BIDIRECTIONAL);
		if (!error)
			goto err;
	} else {
		error = dma_map_sg(dev, req->src, sg_nents(req->src),
				   DMA_TO_DEVICE);
		if (!error)
			goto err;
		error = dma_map_sg(dev, req->dst, sg_nents(req->dst),
				   DMA_FROM_DEVICE);
		if (!error) {
			dma_unmap_sg(dev, req->src, sg_nents(req->src),
				   DMA_TO_DEVICE);
			goto err;
		}
	}

	return 0;
err:
	return -ENOMEM;
}