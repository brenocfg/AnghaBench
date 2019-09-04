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
struct crypto_aead {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_aead_ctx {int /*<<< orphan*/  enc_keylen; int /*<<< orphan*/  enckey_dma_addr; } ;
struct aead_request {int dummy; } ;
struct aead_req_ctx {int /*<<< orphan*/  gcm_iv_inc2_dma_addr; int /*<<< orphan*/  plaintext_authenticate_only; scalar_t__ cryptlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  DRV_CIPHER_GCTR ; 
 int /*<<< orphan*/  DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE1 ; 
 int /*<<< orphan*/  S_DIN_to_AES ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_key_size_aes (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_set_gctr_desc(struct aead_request *req, struct cc_hw_desc desc[],
			     unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int idx = *seq_size;

	/* load key to AES*/
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_GCTR);
	set_cipher_config0(&desc[idx], DRV_CRYPTO_DIRECTION_ENCRYPT);
	set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
		     ctx->enc_keylen, NS_BIT);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	if (req_ctx->cryptlen && !req_ctx->plaintext_authenticate_only) {
		/* load AES/CTR initial CTR value inc by 2*/
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], DRV_CIPHER_GCTR);
		set_key_size_aes(&desc[idx], ctx->enc_keylen);
		set_din_type(&desc[idx], DMA_DLLI,
			     req_ctx->gcm_iv_inc2_dma_addr, AES_BLOCK_SIZE,
			     NS_BIT);
		set_cipher_config0(&desc[idx], DRV_CRYPTO_DIRECTION_ENCRYPT);
		set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
		set_flow_mode(&desc[idx], S_DIN_to_AES);
		idx++;
	}

	*seq_size = idx;
}