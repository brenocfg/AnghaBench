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
typedef  scalar_t__ u64 ;
struct safexcel_result_desc {int dummy; } ;
struct safexcel_crypto_priv {int /*<<< orphan*/  dev; TYPE_1__* ring; } ;
struct safexcel_ahash_req {int /*<<< orphan*/  cache_next; int /*<<< orphan*/  cache; int /*<<< orphan*/  state; scalar_t__ finish; scalar_t__ cache_dma; int /*<<< orphan*/  cache_sz; scalar_t__ result_dma; int /*<<< orphan*/  state_sz; scalar_t__ nents; } ;
struct crypto_async_request {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int /*<<< orphan*/  result; int /*<<< orphan*/  src; } ;
struct TYPE_2__ {int /*<<< orphan*/  rdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ IS_ERR (struct safexcel_result_desc*) ; 
 int PTR_ERR (struct safexcel_result_desc*) ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 scalar_t__ crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  safexcel_complete (struct safexcel_crypto_priv*,int) ; 
 scalar_t__ safexcel_queued_len (struct safexcel_ahash_req*) ; 
 int safexcel_rdesc_check_errors (struct safexcel_crypto_priv*,struct safexcel_result_desc*) ; 
 struct safexcel_result_desc* safexcel_ring_next_rptr (struct safexcel_crypto_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int safexcel_handle_req_result(struct safexcel_crypto_priv *priv, int ring,
				      struct crypto_async_request *async,
				      bool *should_complete, int *ret)
{
	struct safexcel_result_desc *rdesc;
	struct ahash_request *areq = ahash_request_cast(async);
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	struct safexcel_ahash_req *sreq = ahash_request_ctx(areq);
	u64 cache_len;

	*ret = 0;

	rdesc = safexcel_ring_next_rptr(priv, &priv->ring[ring].rdr);
	if (IS_ERR(rdesc)) {
		dev_err(priv->dev,
			"hash: result: could not retrieve the result descriptor\n");
		*ret = PTR_ERR(rdesc);
	} else {
		*ret = safexcel_rdesc_check_errors(priv, rdesc);
	}

	safexcel_complete(priv, ring);

	if (sreq->nents) {
		dma_unmap_sg(priv->dev, areq->src, sreq->nents, DMA_TO_DEVICE);
		sreq->nents = 0;
	}

	if (sreq->result_dma) {
		dma_unmap_single(priv->dev, sreq->result_dma, sreq->state_sz,
				 DMA_FROM_DEVICE);
		sreq->result_dma = 0;
	}

	if (sreq->cache_dma) {
		dma_unmap_single(priv->dev, sreq->cache_dma, sreq->cache_sz,
				 DMA_TO_DEVICE);
		sreq->cache_dma = 0;
	}

	if (sreq->finish)
		memcpy(areq->result, sreq->state,
		       crypto_ahash_digestsize(ahash));

	cache_len = safexcel_queued_len(sreq);
	if (cache_len)
		memcpy(sreq->cache, sreq->cache_next, cache_len);

	*should_complete = true;

	return 1;
}