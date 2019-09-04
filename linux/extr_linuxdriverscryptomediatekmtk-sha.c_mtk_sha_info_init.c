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
struct mtk_sha_info {int* tfm; int* ctrl; int* cmd; } ;
struct mtk_sha_reqctx {int flags; int /*<<< orphan*/  ds; int /*<<< orphan*/  ct_size; int /*<<< orphan*/  ct_hdr; struct mtk_sha_info info; } ;

/* Variables and functions */
 int SHA_CMD0 ; 
 int SHA_CMD1 ; 
 int SHA_CMD2 ; 
 int /*<<< orphan*/  SHA_CT_CTRL_HDR ; 
 int /*<<< orphan*/  SHA_CT_SIZE ; 
 int SHA_FLAGS_ALGO_MSK ; 
#define  SHA_FLAGS_SHA1 132 
#define  SHA_FLAGS_SHA224 131 
#define  SHA_FLAGS_SHA256 130 
#define  SHA_FLAGS_SHA384 129 
#define  SHA_FLAGS_SHA512 128 
 int SHA_TFM_CONTINUE ; 
 int SHA_TFM_DIGEST (int /*<<< orphan*/ ) ; 
 int SHA_TFM_HASH ; 
 int SHA_TFM_HASH_STORE ; 
 int SHA_TFM_SHA1 ; 
 int SHA_TFM_SHA224 ; 
 int SHA_TFM_SHA256 ; 
 int SHA_TFM_SHA384 ; 
 int SHA_TFM_SHA512 ; 
 int SHA_TFM_SIZE (int /*<<< orphan*/ ) ; 
 int SHA_TFM_START ; 
 int /*<<< orphan*/  SIZE_IN_WORDS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_sha_info_init(struct mtk_sha_reqctx *ctx)
{
	struct mtk_sha_info *info = &ctx->info;

	ctx->ct_hdr = SHA_CT_CTRL_HDR;
	ctx->ct_size = SHA_CT_SIZE;

	info->tfm[0] = SHA_TFM_HASH | SHA_TFM_SIZE(SIZE_IN_WORDS(ctx->ds));

	switch (ctx->flags & SHA_FLAGS_ALGO_MSK) {
	case SHA_FLAGS_SHA1:
		info->tfm[0] |= SHA_TFM_SHA1;
		break;
	case SHA_FLAGS_SHA224:
		info->tfm[0] |= SHA_TFM_SHA224;
		break;
	case SHA_FLAGS_SHA256:
		info->tfm[0] |= SHA_TFM_SHA256;
		break;
	case SHA_FLAGS_SHA384:
		info->tfm[0] |= SHA_TFM_SHA384;
		break;
	case SHA_FLAGS_SHA512:
		info->tfm[0] |= SHA_TFM_SHA512;
		break;

	default:
		/* Should not happen... */
		return;
	}

	info->tfm[1] = SHA_TFM_HASH_STORE;
	info->ctrl[0] = info->tfm[0] | SHA_TFM_CONTINUE | SHA_TFM_START;
	info->ctrl[1] = info->tfm[1];

	info->cmd[0] = SHA_CMD0;
	info->cmd[1] = SHA_CMD1;
	info->cmd[2] = SHA_CMD2 | SHA_TFM_DIGEST(SIZE_IN_WORDS(ctx->ds));
}