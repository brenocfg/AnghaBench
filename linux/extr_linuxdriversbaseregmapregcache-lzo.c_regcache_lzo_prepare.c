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
struct regcache_lzo_ctx {int /*<<< orphan*/  wmem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LZO1X_MEM_COMPRESS ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regcache_lzo_prepare(struct regcache_lzo_ctx *lzo_ctx)
{
	lzo_ctx->wmem = kmalloc(LZO1X_MEM_COMPRESS, GFP_KERNEL);
	if (!lzo_ctx->wmem)
		return -ENOMEM;
	return 0;
}