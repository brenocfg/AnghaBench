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
struct cc_ivgen_ctx {int /*<<< orphan*/  next_iv_ofs; int /*<<< orphan*/  pool; int /*<<< orphan*/  ctr_iv; int /*<<< orphan*/  ctr_key; } ;
struct cc_hw_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_KEYSIZE_128 ; 
 int /*<<< orphan*/  CC_AES_128_BIT_KEY_SIZE ; 
 int /*<<< orphan*/  CC_AES_IV_SIZE ; 
 scalar_t__ CC_IVPOOL_GEN_SEQ_LEN ; 
 int /*<<< orphan*/  CC_IVPOOL_META_SIZE ; 
 scalar_t__ CC_IVPOOL_SEQ_LEN ; 
 int /*<<< orphan*/  CC_IVPOOL_SIZE ; 
 int /*<<< orphan*/  DESC_DIRECTION_ENCRYPT_ENCRYPT ; 
 int /*<<< orphan*/  DIN_AES_DOUT ; 
 int /*<<< orphan*/  DRV_CIPHER_CTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE1 ; 
 int /*<<< orphan*/  S_DIN_to_AES ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_const (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_sram (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_sram (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_key_size_aes (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_gen_iv_pool(struct cc_ivgen_ctx *ivgen_ctx,
			  struct cc_hw_desc iv_seq[], unsigned int *iv_seq_len)
{
	unsigned int idx = *iv_seq_len;

	if ((*iv_seq_len + CC_IVPOOL_GEN_SEQ_LEN) > CC_IVPOOL_SEQ_LEN) {
		/* The sequence will be longer than allowed */
		return -EINVAL;
	}
	/* Setup key */
	hw_desc_init(&iv_seq[idx]);
	set_din_sram(&iv_seq[idx], ivgen_ctx->ctr_key, AES_KEYSIZE_128);
	set_setup_mode(&iv_seq[idx], SETUP_LOAD_KEY0);
	set_cipher_config0(&iv_seq[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	set_flow_mode(&iv_seq[idx], S_DIN_to_AES);
	set_key_size_aes(&iv_seq[idx], CC_AES_128_BIT_KEY_SIZE);
	set_cipher_mode(&iv_seq[idx], DRV_CIPHER_CTR);
	idx++;

	/* Setup cipher state */
	hw_desc_init(&iv_seq[idx]);
	set_din_sram(&iv_seq[idx], ivgen_ctx->ctr_iv, CC_AES_IV_SIZE);
	set_cipher_config0(&iv_seq[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	set_flow_mode(&iv_seq[idx], S_DIN_to_AES);
	set_setup_mode(&iv_seq[idx], SETUP_LOAD_STATE1);
	set_key_size_aes(&iv_seq[idx], CC_AES_128_BIT_KEY_SIZE);
	set_cipher_mode(&iv_seq[idx], DRV_CIPHER_CTR);
	idx++;

	/* Perform dummy encrypt to skip first block */
	hw_desc_init(&iv_seq[idx]);
	set_din_const(&iv_seq[idx], 0, CC_AES_IV_SIZE);
	set_dout_sram(&iv_seq[idx], ivgen_ctx->pool, CC_AES_IV_SIZE);
	set_flow_mode(&iv_seq[idx], DIN_AES_DOUT);
	idx++;

	/* Generate IV pool */
	hw_desc_init(&iv_seq[idx]);
	set_din_const(&iv_seq[idx], 0, CC_IVPOOL_SIZE);
	set_dout_sram(&iv_seq[idx], ivgen_ctx->pool, CC_IVPOOL_SIZE);
	set_flow_mode(&iv_seq[idx], DIN_AES_DOUT);
	idx++;

	*iv_seq_len = idx; /* Update sequence length */

	/* queue ordering assures pool readiness */
	ivgen_ctx->next_iv_ofs = CC_IVPOOL_META_SIZE;

	return 0;
}