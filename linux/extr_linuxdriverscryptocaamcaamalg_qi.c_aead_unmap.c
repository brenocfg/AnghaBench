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
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_4__ {TYPE_1__* drv_ctx; } ;
struct aead_edesc {int /*<<< orphan*/  assoclen_dma; int /*<<< orphan*/  qm_sg_bytes; int /*<<< orphan*/  qm_sg_dma; TYPE_2__ drv_req; int /*<<< orphan*/  iv_dma; int /*<<< orphan*/  dst_nents; int /*<<< orphan*/  src_nents; } ;
struct TYPE_3__ {int /*<<< orphan*/  op_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  caam_unmap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aead_unmap(struct device *dev,
		       struct aead_edesc *edesc,
		       struct aead_request *req)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	int ivsize = crypto_aead_ivsize(aead);

	caam_unmap(dev, req->src, req->dst, edesc->src_nents, edesc->dst_nents,
		   edesc->iv_dma, ivsize, edesc->drv_req.drv_ctx->op_type,
		   edesc->qm_sg_dma, edesc->qm_sg_bytes);
	dma_unmap_single(dev, edesc->assoclen_dma, 4, DMA_TO_DEVICE);
}