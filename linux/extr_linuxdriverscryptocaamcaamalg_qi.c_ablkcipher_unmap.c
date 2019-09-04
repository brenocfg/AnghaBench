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
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_3__ {TYPE_2__* drv_ctx; } ;
struct ablkcipher_edesc {int /*<<< orphan*/  qm_sg_bytes; int /*<<< orphan*/  qm_sg_dma; TYPE_1__ drv_req; int /*<<< orphan*/  iv_dma; int /*<<< orphan*/  dst_nents; int /*<<< orphan*/  src_nents; } ;
struct TYPE_4__ {int /*<<< orphan*/  op_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  caam_unmap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 

__attribute__((used)) static void ablkcipher_unmap(struct device *dev,
			     struct ablkcipher_edesc *edesc,
			     struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *ablkcipher = crypto_ablkcipher_reqtfm(req);
	int ivsize = crypto_ablkcipher_ivsize(ablkcipher);

	caam_unmap(dev, req->src, req->dst, edesc->src_nents, edesc->dst_nents,
		   edesc->iv_dma, ivsize, edesc->drv_req.drv_ctx->op_type,
		   edesc->qm_sg_dma, edesc->qm_sg_bytes);
}