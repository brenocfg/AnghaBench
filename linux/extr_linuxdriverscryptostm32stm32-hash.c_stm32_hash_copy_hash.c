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
struct stm32_hash_request_ctx {int flags; int /*<<< orphan*/  hdev; scalar_t__ digest; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int HASH_FLAGS_ALGO_MASK ; 
#define  HASH_FLAGS_MD5 131 
#define  HASH_FLAGS_SHA1 130 
#define  HASH_FLAGS_SHA224 129 
#define  HASH_FLAGS_SHA256 128 
 int /*<<< orphan*/  HASH_HREG (unsigned int) ; 
 unsigned int MD5_DIGEST_SIZE ; 
 unsigned int SHA1_DIGEST_SIZE ; 
 unsigned int SHA224_DIGEST_SIZE ; 
 unsigned int SHA256_DIGEST_SIZE ; 
 struct stm32_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_hash_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_hash_copy_hash(struct ahash_request *req)
{
	struct stm32_hash_request_ctx *rctx = ahash_request_ctx(req);
	u32 *hash = (u32 *)rctx->digest;
	unsigned int i, hashsize;

	switch (rctx->flags & HASH_FLAGS_ALGO_MASK) {
	case HASH_FLAGS_MD5:
		hashsize = MD5_DIGEST_SIZE;
		break;
	case HASH_FLAGS_SHA1:
		hashsize = SHA1_DIGEST_SIZE;
		break;
	case HASH_FLAGS_SHA224:
		hashsize = SHA224_DIGEST_SIZE;
		break;
	case HASH_FLAGS_SHA256:
		hashsize = SHA256_DIGEST_SIZE;
		break;
	default:
		return;
	}

	for (i = 0; i < hashsize / sizeof(u32); i++)
		hash[i] = be32_to_cpu(stm32_hash_read(rctx->hdev,
						      HASH_HREG(i)));
}