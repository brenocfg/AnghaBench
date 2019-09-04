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
struct aead_req_ctx {int /*<<< orphan*/  hkey_dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  DIN_AES_DOUT ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  DRV_CIPHER_ECB ; 
 int /*<<< orphan*/  DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int /*<<< orphan*/  DRV_HASH_HW_GHASH ; 
 int /*<<< orphan*/  HASH_PADDING_ENABLED ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE0 ; 
 int /*<<< orphan*/  S_DIN_to_AES ; 
 int /*<<< orphan*/  S_DIN_to_HASH ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_aes_not_hash_mode (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_config1 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_do (struct cc_hw_desc*,int) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_const (struct cc_hw_desc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_dlli (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_key_size_aes (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_set_ghash_desc(struct aead_request *req,
			      struct cc_hw_desc desc[], unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int idx = *seq_size;

	/* load key to AES*/
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_ECB);
	set_cipher_config0(&desc[idx], DRV_CRYPTO_DIRECTION_ENCRYPT);
	set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
		     ctx->enc_keylen, NS_BIT);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* process one zero block to generate hkey */
	hw_desc_init(&desc[idx]);
	set_din_const(&desc[idx], 0x0, AES_BLOCK_SIZE);
	set_dout_dlli(&desc[idx], req_ctx->hkey_dma_addr, AES_BLOCK_SIZE,
		      NS_BIT, 0);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	idx++;

	/* Memory Barrier */
	hw_desc_init(&desc[idx]);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_dout_no_dma(&desc[idx], 0, 0, 1);
	idx++;

	/* Load GHASH subkey */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->hkey_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_dout_no_dma(&desc[idx], 0, 0, 1);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_HASH_HW_GHASH);
	set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	/* Configure Hash Engine to work with GHASH.
	 * Since it was not possible to extend HASH submodes to add GHASH,
	 * The following command is necessary in order to
	 * select GHASH (according to HW designers)
	 */
	hw_desc_init(&desc[idx]);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_dout_no_dma(&desc[idx], 0, 0, 1);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_HASH_HW_GHASH);
	set_cipher_do(&desc[idx], 1); //1=AES_SK RKEK
	set_cipher_config0(&desc[idx], DRV_CRYPTO_DIRECTION_ENCRYPT);
	set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	/* Load GHASH initial STATE (which is 0). (for any hash there is an
	 * initial state)
	 */
	hw_desc_init(&desc[idx]);
	set_din_const(&desc[idx], 0x0, AES_BLOCK_SIZE);
	set_dout_no_dma(&desc[idx], 0, 0, 1);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_HASH_HW_GHASH);
	set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	*seq_size = idx;
}