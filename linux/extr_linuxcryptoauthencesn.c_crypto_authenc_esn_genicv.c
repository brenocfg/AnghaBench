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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
struct crypto_authenc_esn_ctx {scalar_t__ reqoff; struct crypto_ahash* auth; } ;
struct crypto_ahash {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct authenc_esn_request_ctx {int /*<<< orphan*/  dst; scalar_t__ tail; } ;
struct ahash_request {int dummy; } ;
struct aead_request {unsigned int assoclen; unsigned int cryptlen; struct scatterlist* dst; } ;

/* Variables and functions */
 int /*<<< orphan*/ * PTR_ALIGN (int /*<<< orphan*/ *,scalar_t__) ; 
 struct authenc_esn_request_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,unsigned int,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (struct ahash_request*,struct crypto_ahash*) ; 
 int /*<<< orphan*/  authenc_esn_geniv_ahash_done ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_authenc_esn_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 scalar_t__ crypto_ahash_alignmask (struct crypto_ahash*) ; 
 scalar_t__ crypto_ahash_digest (struct ahash_request*) ; 
 int crypto_authenc_esn_genicv_tail (struct aead_request*,int /*<<< orphan*/ ) ; 
 struct scatterlist* scatterwalk_ffwd (int /*<<< orphan*/ ,struct scatterlist*,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,struct scatterlist*,unsigned int,int,int) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int crypto_authenc_esn_genicv(struct aead_request *req,
				     unsigned int flags)
{
	struct crypto_aead *authenc_esn = crypto_aead_reqtfm(req);
	struct authenc_esn_request_ctx *areq_ctx = aead_request_ctx(req);
	struct crypto_authenc_esn_ctx *ctx = crypto_aead_ctx(authenc_esn);
	struct crypto_ahash *auth = ctx->auth;
	u8 *hash = PTR_ALIGN((u8 *)areq_ctx->tail,
			     crypto_ahash_alignmask(auth) + 1);
	struct ahash_request *ahreq = (void *)(areq_ctx->tail + ctx->reqoff);
	unsigned int authsize = crypto_aead_authsize(authenc_esn);
	unsigned int assoclen = req->assoclen;
	unsigned int cryptlen = req->cryptlen;
	struct scatterlist *dst = req->dst;
	u32 tmp[2];

	if (!authsize)
		return 0;

	/* Move high-order bits of sequence number to the end. */
	scatterwalk_map_and_copy(tmp, dst, 0, 8, 0);
	scatterwalk_map_and_copy(tmp, dst, 4, 4, 1);
	scatterwalk_map_and_copy(tmp + 1, dst, assoclen + cryptlen, 4, 1);

	sg_init_table(areq_ctx->dst, 2);
	dst = scatterwalk_ffwd(areq_ctx->dst, dst, 4);

	ahash_request_set_tfm(ahreq, auth);
	ahash_request_set_crypt(ahreq, dst, hash, assoclen + cryptlen);
	ahash_request_set_callback(ahreq, flags,
				   authenc_esn_geniv_ahash_done, req);

	return crypto_ahash_digest(ahreq) ?:
	       crypto_authenc_esn_genicv_tail(req, aead_request_flags(req));
}