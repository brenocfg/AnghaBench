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
struct scatterlist {int dummy; } ;
struct safexcel_result_desc {int /*<<< orphan*/  last_seg; } ;
struct safexcel_crypto_priv {int /*<<< orphan*/  dev; TYPE_1__* ring; } ;
struct safexcel_cipher_req {int dummy; } ;
struct crypto_async_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ IS_ERR (struct safexcel_result_desc*) ; 
 int PTR_ERR (struct safexcel_result_desc*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  safexcel_complete (struct safexcel_crypto_priv*,int) ; 
 int safexcel_rdesc_check_errors (struct safexcel_crypto_priv*,struct safexcel_result_desc*) ; 
 struct safexcel_result_desc* safexcel_ring_next_rptr (struct safexcel_crypto_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_nents_for_len (struct scatterlist*,unsigned int) ; 

__attribute__((used)) static int safexcel_handle_req_result(struct safexcel_crypto_priv *priv, int ring,
				      struct crypto_async_request *async,
				      struct scatterlist *src,
				      struct scatterlist *dst,
				      unsigned int cryptlen,
				      struct safexcel_cipher_req *sreq,
				      bool *should_complete, int *ret)
{
	struct safexcel_result_desc *rdesc;
	int ndesc = 0;

	*ret = 0;

	do {
		rdesc = safexcel_ring_next_rptr(priv, &priv->ring[ring].rdr);
		if (IS_ERR(rdesc)) {
			dev_err(priv->dev,
				"cipher: result: could not retrieve the result descriptor\n");
			*ret = PTR_ERR(rdesc);
			break;
		}

		if (likely(!*ret))
			*ret = safexcel_rdesc_check_errors(priv, rdesc);

		ndesc++;
	} while (!rdesc->last_seg);

	safexcel_complete(priv, ring);

	if (src == dst) {
		dma_unmap_sg(priv->dev, src,
			     sg_nents_for_len(src, cryptlen),
			     DMA_BIDIRECTIONAL);
	} else {
		dma_unmap_sg(priv->dev, src,
			     sg_nents_for_len(src, cryptlen),
			     DMA_TO_DEVICE);
		dma_unmap_sg(priv->dev, dst,
			     sg_nents_for_len(dst, cryptlen),
			     DMA_FROM_DEVICE);
	}

	*should_complete = true;

	return ndesc;
}