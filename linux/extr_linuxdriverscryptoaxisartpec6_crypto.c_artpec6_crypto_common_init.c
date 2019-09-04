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
struct scatterlist {int dummy; } ;
struct crypto_async_request {int flags; } ;
struct artpec6_crypto_req_common {void (* complete ) (struct crypto_async_request*) ;struct crypto_async_request* req; int /*<<< orphan*/  dma; int /*<<< orphan*/  gfp_flags; } ;
struct artpec6_crypto {int /*<<< orphan*/  dma_cache; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  artpec6_crypto_dev ; 
 struct artpec6_crypto* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int artpec6_crypto_common_init(struct artpec6_crypto_req_common *common,
		struct crypto_async_request *parent,
		void (*complete)(struct crypto_async_request *req),
		struct scatterlist *dstsg, unsigned int nbytes)
{
	gfp_t flags;
	struct artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);

	flags = (parent->flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		 GFP_KERNEL : GFP_ATOMIC;

	common->gfp_flags = flags;
	common->dma = kmem_cache_alloc(ac->dma_cache, flags);
	if (!common->dma)
		return -ENOMEM;

	common->req = parent;
	common->complete = complete;
	return 0;
}