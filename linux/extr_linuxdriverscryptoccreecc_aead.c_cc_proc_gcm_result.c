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
struct crypto_aead {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_aead_ctx {int /*<<< orphan*/  drvdata; int /*<<< orphan*/  authsize; int /*<<< orphan*/  enc_keylen; } ;
struct aead_request {int dummy; } ;
struct TYPE_2__ {scalar_t__ op_type; } ;
struct aead_req_ctx {int /*<<< orphan*/  mac_buf_dma_addr; int /*<<< orphan*/  gcm_iv_inc1_dma_addr; int /*<<< orphan*/  gcm_block_len_dma_addr; int /*<<< orphan*/  icv_dma_addr; TYPE_1__ gen_ctx; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  DIN_AES_DOUT ; 
 int /*<<< orphan*/  DIN_HASH ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  DRV_CIPHER_GCTR ; 
 scalar_t__ DRV_CRYPTO_DIRECTION_DECRYPT ; 
 int /*<<< orphan*/  DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int /*<<< orphan*/  DRV_HASH_HW_GHASH ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE1 ; 
 int /*<<< orphan*/  SETUP_WRITE_STATE0 ; 
 int /*<<< orphan*/  S_DIN_to_AES ; 
 int /*<<< orphan*/  S_HASH_to_DOUT ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_aes_not_hash_mode (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_dlli (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dout_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_key_size_aes (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_queue_last_ind (int /*<<< orphan*/ ,struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_proc_gcm_result(struct aead_request *req,
			       struct cc_hw_desc desc[],
			       unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	dma_addr_t mac_result;
	unsigned int idx = *seq_size;

	if (req_ctx->gen_ctx.op_type == DRV_CRYPTO_DIRECTION_DECRYPT) {
		mac_result = req_ctx->mac_buf_dma_addr;
	} else { /* Encrypt */
		mac_result = req_ctx->icv_dma_addr;
	}

	/* process(ghash) gcm_block_len */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->gcm_block_len_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_flow_mode(&desc[idx], DIN_HASH);
	idx++;

	/* Store GHASH state after GHASH(Associated Data + Cipher +LenBlock) */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_HASH_HW_GHASH);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_dout_dlli(&desc[idx], req_ctx->mac_buf_dma_addr, AES_BLOCK_SIZE,
		      NS_BIT, 0);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_aes_not_hash_mode(&desc[idx]);

	idx++;

	/* load AES/CTR initial CTR value inc by 1*/
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_GCTR);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->gcm_iv_inc1_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_cipher_config0(&desc[idx], DRV_CRYPTO_DIRECTION_ENCRYPT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Memory Barrier */
	hw_desc_init(&desc[idx]);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_dout_no_dma(&desc[idx], 0, 0, 1);
	idx++;

	/* process GCTR on stored GHASH and store MAC in mac_state*/
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_GCTR);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->mac_buf_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_dout_dlli(&desc[idx], mac_result, ctx->authsize, NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	idx++;

	*seq_size = idx;
}