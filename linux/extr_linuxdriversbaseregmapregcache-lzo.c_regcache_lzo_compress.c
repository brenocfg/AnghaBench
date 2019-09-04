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
struct regcache_lzo_ctx {size_t dst_len; int /*<<< orphan*/  wmem; int /*<<< orphan*/  dst; int /*<<< orphan*/  src_len; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int EINVAL ; 
 int LZO_E_OK ; 
 int lzo1x_1_compress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regcache_lzo_compress(struct regcache_lzo_ctx *lzo_ctx)
{
	size_t compress_size;
	int ret;

	ret = lzo1x_1_compress(lzo_ctx->src, lzo_ctx->src_len,
			       lzo_ctx->dst, &compress_size, lzo_ctx->wmem);
	if (ret != LZO_E_OK || compress_size > lzo_ctx->dst_len)
		return -EINVAL;
	lzo_ctx->dst_len = compress_size;
	return 0;
}