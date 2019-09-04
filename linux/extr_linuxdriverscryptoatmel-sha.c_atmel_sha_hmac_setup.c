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
struct crypto_ahash {int dummy; } ;
struct atmel_sha_reqctx {int flags; size_t block_size; void* hash_size; } ;
struct atmel_sha_hmac_ctx {int (* resume ) (struct atmel_sha_dev*) ;scalar_t__ ipad; int /*<<< orphan*/  hkey; } ;
struct atmel_sha_dev {struct ahash_request* req; } ;
struct ahash_request {int dummy; } ;
typedef  int (* atmel_sha_fn_t ) (struct atmel_sha_dev*) ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 size_t SHA1_BLOCK_SIZE ; 
 void* SHA1_DIGEST_SIZE ; 
 size_t SHA224_BLOCK_SIZE ; 
 size_t SHA256_BLOCK_SIZE ; 
 void* SHA256_DIGEST_SIZE ; 
 size_t SHA384_BLOCK_SIZE ; 
 size_t SHA512_BLOCK_SIZE ; 
 void* SHA512_DIGEST_SIZE ; 
 int SHA_FLAGS_ALGO_MASK ; 
#define  SHA_FLAGS_SHA1 132 
#define  SHA_FLAGS_SHA224 131 
#define  SHA_FLAGS_SHA256 130 
#define  SHA_FLAGS_SHA384 129 
#define  SHA_FLAGS_SHA512 128 
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int atmel_sha_complete (struct atmel_sha_dev*,int /*<<< orphan*/ ) ; 
 int atmel_sha_hmac_compute_ipad_hash (struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  atmel_sha_hmac_key_get (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,unsigned int*) ; 
 int atmel_sha_hmac_prehash_key (struct atmel_sha_dev*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct atmel_sha_hmac_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atmel_sha_hmac_setup(struct atmel_sha_dev *dd,
				atmel_sha_fn_t resume)
{
	struct ahash_request *req = dd->req;
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct atmel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	unsigned int keylen;
	const u8 *key;
	size_t bs;

	hmac->resume = resume;
	switch (ctx->flags & SHA_FLAGS_ALGO_MASK) {
	case SHA_FLAGS_SHA1:
		ctx->block_size = SHA1_BLOCK_SIZE;
		ctx->hash_size = SHA1_DIGEST_SIZE;
		break;

	case SHA_FLAGS_SHA224:
		ctx->block_size = SHA224_BLOCK_SIZE;
		ctx->hash_size = SHA256_DIGEST_SIZE;
		break;

	case SHA_FLAGS_SHA256:
		ctx->block_size = SHA256_BLOCK_SIZE;
		ctx->hash_size = SHA256_DIGEST_SIZE;
		break;

	case SHA_FLAGS_SHA384:
		ctx->block_size = SHA384_BLOCK_SIZE;
		ctx->hash_size = SHA512_DIGEST_SIZE;
		break;

	case SHA_FLAGS_SHA512:
		ctx->block_size = SHA512_BLOCK_SIZE;
		ctx->hash_size = SHA512_DIGEST_SIZE;
		break;

	default:
		return atmel_sha_complete(dd, -EINVAL);
	}
	bs = ctx->block_size;

	if (likely(!atmel_sha_hmac_key_get(&hmac->hkey, &key, &keylen)))
		return resume(dd);

	/* Compute K' from K. */
	if (unlikely(keylen > bs))
		return atmel_sha_hmac_prehash_key(dd, key, keylen);

	/* Prepare ipad. */
	memcpy((u8 *)hmac->ipad, key, keylen);
	memset((u8 *)hmac->ipad + keylen, 0, bs - keylen);
	return atmel_sha_hmac_compute_ipad_hash(dd);
}