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
struct TYPE_2__ {int /*<<< orphan*/ * digest; } ;
struct mtk_sha_reqctx {int flags; int /*<<< orphan*/  ds; TYPE_1__ info; } ;
struct ahash_request {scalar_t__ result; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int SHA_FLAGS_HMAC ; 
 int SIZE_IN_WORDS (int /*<<< orphan*/ ) ; 
 struct mtk_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int mtk_sha_finish_hmac (struct ahash_request*) ; 

__attribute__((used)) static int mtk_sha_finish(struct ahash_request *req)
{
	struct mtk_sha_reqctx *ctx = ahash_request_ctx(req);
	__le32 *digest = ctx->info.digest;
	u32 *result = (u32 *)req->result;
	int i;

	/* Get the hash from the digest buffer */
	for (i = 0; i < SIZE_IN_WORDS(ctx->ds); i++)
		result[i] = le32_to_cpu(digest[i]);

	if (ctx->flags & SHA_FLAGS_HMAC)
		return mtk_sha_finish_hmac(req);

	return 0;
}