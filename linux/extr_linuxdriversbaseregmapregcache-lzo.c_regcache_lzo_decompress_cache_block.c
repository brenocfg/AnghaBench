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
struct regmap {int dummy; } ;
struct regcache_lzo_ctx {scalar_t__ dst_len; int /*<<< orphan*/  dst; scalar_t__ decompressed_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int regcache_lzo_decompress (struct regcache_lzo_ctx*) ; 

__attribute__((used)) static int regcache_lzo_decompress_cache_block(struct regmap *map,
		struct regcache_lzo_ctx *lzo_ctx)
{
	int ret;

	lzo_ctx->dst_len = lzo_ctx->decompressed_size;
	lzo_ctx->dst = kmalloc(lzo_ctx->dst_len, GFP_KERNEL);
	if (!lzo_ctx->dst) {
		lzo_ctx->dst_len = 0;
		return -ENOMEM;
	}

	ret = regcache_lzo_decompress(lzo_ctx);
	if (ret < 0)
		return ret;
	return 0;
}