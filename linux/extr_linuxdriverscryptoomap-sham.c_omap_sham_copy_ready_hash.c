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
struct omap_sham_reqctx {int flags; TYPE_1__* dd; scalar_t__ digest; } ;
struct ahash_request {scalar_t__ result; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_BE32_SHA1 ; 
 int FLAGS_MODE_MASK ; 
#define  FLAGS_MODE_MD5 133 
#define  FLAGS_MODE_SHA1 132 
#define  FLAGS_MODE_SHA224 131 
#define  FLAGS_MODE_SHA256 130 
#define  FLAGS_MODE_SHA384 129 
#define  FLAGS_MODE_SHA512 128 
 int MD5_DIGEST_SIZE ; 
 int SHA1_DIGEST_SIZE ; 
 int SHA224_DIGEST_SIZE ; 
 int SHA256_DIGEST_SIZE ; 
 int SHA384_DIGEST_SIZE ; 
 int SHA512_DIGEST_SIZE ; 
 struct omap_sham_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap_sham_copy_ready_hash(struct ahash_request *req)
{
	struct omap_sham_reqctx *ctx = ahash_request_ctx(req);
	u32 *in = (u32 *)ctx->digest;
	u32 *hash = (u32 *)req->result;
	int i, d, big_endian = 0;

	if (!hash)
		return;

	switch (ctx->flags & FLAGS_MODE_MASK) {
	case FLAGS_MODE_MD5:
		d = MD5_DIGEST_SIZE / sizeof(u32);
		break;
	case FLAGS_MODE_SHA1:
		/* OMAP2 SHA1 is big endian */
		if (test_bit(FLAGS_BE32_SHA1, &ctx->dd->flags))
			big_endian = 1;
		d = SHA1_DIGEST_SIZE / sizeof(u32);
		break;
	case FLAGS_MODE_SHA224:
		d = SHA224_DIGEST_SIZE / sizeof(u32);
		break;
	case FLAGS_MODE_SHA256:
		d = SHA256_DIGEST_SIZE / sizeof(u32);
		break;
	case FLAGS_MODE_SHA384:
		d = SHA384_DIGEST_SIZE / sizeof(u32);
		break;
	case FLAGS_MODE_SHA512:
		d = SHA512_DIGEST_SIZE / sizeof(u32);
		break;
	default:
		d = 0;
	}

	if (big_endian)
		for (i = 0; i < d; i++)
			hash[i] = be32_to_cpu(in[i]);
	else
		for (i = 0; i < d; i++)
			hash[i] = le32_to_cpu(in[i]);
}