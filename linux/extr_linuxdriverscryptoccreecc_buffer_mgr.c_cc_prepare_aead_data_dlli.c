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
typedef  unsigned int u32 ;
struct aead_request {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_2__ {int op_type; } ;
struct aead_req_ctx {unsigned int req_authsize; int is_icv_fragmented; unsigned int icv_dma_addr; unsigned int icv_virt_addr; int /*<<< orphan*/  dst_sgl; int /*<<< orphan*/  src_sgl; TYPE_1__ gen_ctx; } ;
typedef  enum drv_crypto_direction { ____Placeholder_drv_crypto_direction } drv_crypto_direction ;

/* Variables and functions */
 int DRV_CRYPTO_DIRECTION_DECRYPT ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 unsigned int sg_dma_address (int /*<<< orphan*/ ) ; 
 unsigned int sg_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_prepare_aead_data_dlli(struct aead_request *req,
				      u32 *src_last_bytes, u32 *dst_last_bytes)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	enum drv_crypto_direction direct = areq_ctx->gen_ctx.op_type;
	unsigned int authsize = areq_ctx->req_authsize;

	areq_ctx->is_icv_fragmented = false;
	if (req->src == req->dst) {
		/*INPLACE*/
		areq_ctx->icv_dma_addr = sg_dma_address(areq_ctx->src_sgl) +
			(*src_last_bytes - authsize);
		areq_ctx->icv_virt_addr = sg_virt(areq_ctx->src_sgl) +
			(*src_last_bytes - authsize);
	} else if (direct == DRV_CRYPTO_DIRECTION_DECRYPT) {
		/*NON-INPLACE and DECRYPT*/
		areq_ctx->icv_dma_addr = sg_dma_address(areq_ctx->src_sgl) +
			(*src_last_bytes - authsize);
		areq_ctx->icv_virt_addr = sg_virt(areq_ctx->src_sgl) +
			(*src_last_bytes - authsize);
	} else {
		/*NON-INPLACE and ENCRYPT*/
		areq_ctx->icv_dma_addr = sg_dma_address(areq_ctx->dst_sgl) +
			(*dst_last_bytes - authsize);
		areq_ctx->icv_virt_addr = sg_virt(areq_ctx->dst_sgl) +
			(*dst_last_bytes - authsize);
	}
}