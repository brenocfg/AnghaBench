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
typedef  int /*<<< orphan*/  u32 ;
struct atmel_sha_reqctx {int flags; int /*<<< orphan*/  dd; scalar_t__ digest; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 unsigned int SHA1_DIGEST_SIZE ; 
 unsigned int SHA256_DIGEST_SIZE ; 
 unsigned int SHA512_DIGEST_SIZE ; 
 int SHA_FLAGS_ALGO_MASK ; 
 int SHA_FLAGS_RESTORE ; 
#define  SHA_FLAGS_SHA1 132 
#define  SHA_FLAGS_SHA224 131 
#define  SHA_FLAGS_SHA256 130 
#define  SHA_FLAGS_SHA384 129 
#define  SHA_FLAGS_SHA512 128 
 int /*<<< orphan*/  SHA_REG_DIGEST (unsigned int) ; 
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  atmel_sha_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_sha_copy_hash(struct ahash_request *req)
{
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);
	u32 *hash = (u32 *)ctx->digest;
	unsigned int i, hashsize;

	switch (ctx->flags & SHA_FLAGS_ALGO_MASK) {
	case SHA_FLAGS_SHA1:
		hashsize = SHA1_DIGEST_SIZE;
		break;

	case SHA_FLAGS_SHA224:
	case SHA_FLAGS_SHA256:
		hashsize = SHA256_DIGEST_SIZE;
		break;

	case SHA_FLAGS_SHA384:
	case SHA_FLAGS_SHA512:
		hashsize = SHA512_DIGEST_SIZE;
		break;

	default:
		/* Should not happen... */
		return;
	}

	for (i = 0; i < hashsize / sizeof(u32); ++i)
		hash[i] = atmel_sha_read(ctx->dd, SHA_REG_DIGEST(i));
	ctx->flags |= SHA_FLAGS_RESTORE;
}