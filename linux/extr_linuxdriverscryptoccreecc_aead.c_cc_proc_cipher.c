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
struct cc_hw_desc {int dummy; } ;
struct aead_request {int dummy; } ;
struct TYPE_2__ {int op_type; } ;
struct aead_req_ctx {scalar_t__ cryptlen; TYPE_1__ gen_ctx; } ;

/* Variables and functions */
 int DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  cc_proc_cipher_desc (struct aead_request*,unsigned int,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_set_cipher_desc (struct aead_request*,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_din_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dout_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cc_proc_cipher(struct aead_request *req, struct cc_hw_desc desc[],
			   unsigned int *seq_size, unsigned int data_flow_mode)
{
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	int direct = req_ctx->gen_ctx.op_type;
	unsigned int idx = *seq_size;

	if (req_ctx->cryptlen == 0)
		return; /*null processing*/

	cc_set_cipher_desc(req, desc, &idx);
	cc_proc_cipher_desc(req, data_flow_mode, desc, &idx);
	if (direct == DRV_CRYPTO_DIRECTION_ENCRYPT) {
		/* We must wait for DMA to write all cipher */
		hw_desc_init(&desc[idx]);
		set_din_no_dma(&desc[idx], 0, 0xfffff0);
		set_dout_no_dma(&desc[idx], 0, 0, 1);
		idx++;
	}

	*seq_size = idx;
}