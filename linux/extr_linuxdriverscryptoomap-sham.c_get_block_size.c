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
struct omap_sham_reqctx {int flags; } ;

/* Variables and functions */
 int FLAGS_MODE_MASK ; 
#define  FLAGS_MODE_MD5 133 
#define  FLAGS_MODE_SHA1 132 
#define  FLAGS_MODE_SHA224 131 
#define  FLAGS_MODE_SHA256 130 
#define  FLAGS_MODE_SHA384 129 
#define  FLAGS_MODE_SHA512 128 
 int SHA1_BLOCK_SIZE ; 
 int SHA256_BLOCK_SIZE ; 
 int SHA512_BLOCK_SIZE ; 

__attribute__((used)) static int get_block_size(struct omap_sham_reqctx *ctx)
{
	int d;

	switch (ctx->flags & FLAGS_MODE_MASK) {
	case FLAGS_MODE_MD5:
	case FLAGS_MODE_SHA1:
		d = SHA1_BLOCK_SIZE;
		break;
	case FLAGS_MODE_SHA224:
	case FLAGS_MODE_SHA256:
		d = SHA256_BLOCK_SIZE;
		break;
	case FLAGS_MODE_SHA384:
	case FLAGS_MODE_SHA512:
		d = SHA512_BLOCK_SIZE;
		break;
	default:
		d = 0;
	}

	return d;
}