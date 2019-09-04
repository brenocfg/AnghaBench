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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  keylen; } ;
struct cc_hash_ctx {scalar_t__ hw_mode; int /*<<< orphan*/  drvdata; TYPE_1__ key_params; } ;
struct cc_crypto_req {void* user_arg; void* user_cb; } ;
struct ahash_request {scalar_t__ nbytes; int /*<<< orphan*/  result; int /*<<< orphan*/  src; int /*<<< orphan*/  base; } ;
struct ahash_req_ctx {scalar_t__ xcbc_count; int /*<<< orphan*/  digest_result_dma_addr; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CC_AES_128_BIT_KEY_SIZE ; 
 int CC_MAX_HASH_SEQ_LEN ; 
 int /*<<< orphan*/  DIN_AES_DOUT ; 
 scalar_t__ DRV_CIPHER_XCBC_MAC ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_WRITE_STATE0 ; 
 int /*<<< orphan*/  S_AES_to_DOUT ; 
 int /*<<< orphan*/  S_DIN_to_AES ; 
 struct ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  cc_gfp_flags (int /*<<< orphan*/ *) ; 
 scalar_t__ cc_hash_complete ; 
 int cc_mac_final (struct ahash_request*) ; 
 scalar_t__ cc_map_hash_request_final (int /*<<< orphan*/ ,struct ahash_req_ctx*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cc_map_req (struct device*,struct ahash_req_ctx*,struct cc_hash_ctx*) ; 
 scalar_t__ cc_map_result (struct device*,struct ahash_req_ctx*,int /*<<< orphan*/ ) ; 
 int cc_send_request (int /*<<< orphan*/ ,struct cc_crypto_req*,struct cc_hw_desc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_set_desc (struct ahash_req_ctx*,struct cc_hash_ctx*,int /*<<< orphan*/ ,struct cc_hw_desc*,int,int*) ; 
 int /*<<< orphan*/  cc_setup_cmac (struct ahash_request*,struct cc_hw_desc*,int*) ; 
 int /*<<< orphan*/  cc_setup_xcbc (struct ahash_request*,struct cc_hw_desc*,int*) ; 
 int /*<<< orphan*/  cc_unmap_hash_request (struct device*,struct ahash_req_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cc_unmap_req (struct device*,struct ahash_req_ctx*,struct cc_hash_ctx*) ; 
 int /*<<< orphan*/  cc_unmap_result (struct device*,struct ahash_req_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cc_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,scalar_t__) ; 
 int /*<<< orphan*/  set_cmac_size0_mode (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_dout_dlli (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_key_size_aes (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_queue_last_ind (int /*<<< orphan*/ ,struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_mac_finup(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	struct device *dev = drvdata_to_dev(ctx->drvdata);
	struct cc_crypto_req cc_req = {};
	struct cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];
	int idx = 0;
	int rc = 0;
	u32 key_len = 0;
	u32 digestsize = crypto_ahash_digestsize(tfm);
	gfp_t flags = cc_gfp_flags(&req->base);

	dev_dbg(dev, "===== finup xcbc(%d) ====\n", req->nbytes);
	if (state->xcbc_count > 0 && req->nbytes == 0) {
		dev_dbg(dev, "No data to update. Call to fdx_mac_final\n");
		return cc_mac_final(req);
	}

	if (cc_map_req(dev, state, ctx)) {
		dev_err(dev, "map_ahash_source() failed\n");
		return -EINVAL;
	}

	if (cc_map_hash_request_final(ctx->drvdata, state, req->src,
				      req->nbytes, 1, flags)) {
		dev_err(dev, "map_ahash_request_final() failed\n");
		cc_unmap_req(dev, state, ctx);
		return -ENOMEM;
	}
	if (cc_map_result(dev, state, digestsize)) {
		dev_err(dev, "map_ahash_digest() failed\n");
		cc_unmap_hash_request(dev, state, req->src, true);
		cc_unmap_req(dev, state, ctx);
		return -ENOMEM;
	}

	/* Setup request structure */
	cc_req.user_cb = (void *)cc_hash_complete;
	cc_req.user_arg = (void *)req;

	if (ctx->hw_mode == DRV_CIPHER_XCBC_MAC) {
		key_len = CC_AES_128_BIT_KEY_SIZE;
		cc_setup_xcbc(req, desc, &idx);
	} else {
		key_len = ctx->key_params.keylen;
		cc_setup_cmac(req, desc, &idx);
	}

	if (req->nbytes == 0) {
		hw_desc_init(&desc[idx]);
		set_cipher_mode(&desc[idx], ctx->hw_mode);
		set_key_size_aes(&desc[idx], key_len);
		set_cmac_size0_mode(&desc[idx]);
		set_flow_mode(&desc[idx], S_DIN_to_AES);
		idx++;
	} else {
		cc_set_desc(state, ctx, DIN_AES_DOUT, desc, false, &idx);
	}

	/* Get final MAC result */
	hw_desc_init(&desc[idx]);
	/* TODO */
	set_dout_dlli(&desc[idx], state->digest_result_dma_addr,
		      digestsize, NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], S_AES_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	set_cipher_mode(&desc[idx], ctx->hw_mode);
	idx++;

	rc = cc_send_request(ctx->drvdata, &cc_req, desc, idx, &req->base);
	if (rc != -EINPROGRESS && rc != -EBUSY) {
		dev_err(dev, "send_request() failed (rc=%d)\n", rc);
		cc_unmap_hash_request(dev, state, req->src, true);
		cc_unmap_result(dev, state, digestsize, req->result);
		cc_unmap_req(dev, state, ctx);
	}
	return rc;
}