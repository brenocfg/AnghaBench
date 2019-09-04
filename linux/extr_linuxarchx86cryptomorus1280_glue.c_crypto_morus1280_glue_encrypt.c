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
struct morus1280_ops {int /*<<< orphan*/  crypt_tail; int /*<<< orphan*/  crypt_blocks; int /*<<< orphan*/  skcipher_walk_init; } ;
struct morus1280_ctx {TYPE_1__* ops; } ;
struct morus1280_block {int /*<<< orphan*/  bytes; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {unsigned int cryptlen; scalar_t__ assoclen; int /*<<< orphan*/  dst; } ;
struct TYPE_2__ {int /*<<< orphan*/  enc_tail; int /*<<< orphan*/  enc; } ;

/* Variables and functions */
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct morus1280_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_morus1280_glue_crypt (struct aead_request*,struct morus1280_ops,unsigned int,struct morus1280_block*) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int,int) ; 
 int /*<<< orphan*/  skcipher_walk_aead_encrypt ; 

int crypto_morus1280_glue_encrypt(struct aead_request *req)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct morus1280_ctx *ctx = crypto_aead_ctx(tfm);
	struct morus1280_ops OPS = {
		.skcipher_walk_init = skcipher_walk_aead_encrypt,
		.crypt_blocks = ctx->ops->enc,
		.crypt_tail = ctx->ops->enc_tail,
	};

	struct morus1280_block tag = {};
	unsigned int authsize = crypto_aead_authsize(tfm);
	unsigned int cryptlen = req->cryptlen;

	crypto_morus1280_glue_crypt(req, OPS, cryptlen, &tag);

	scatterwalk_map_and_copy(tag.bytes, req->dst,
				 req->assoclen + cryptlen, authsize, 1);
	return 0;
}