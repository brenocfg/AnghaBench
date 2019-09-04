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
struct md5_state {int /*<<< orphan*/  block; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu_array (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  md5_transform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void md5_transform_helper(struct md5_state *ctx)
{
	le32_to_cpu_array(ctx->block, sizeof(ctx->block) / sizeof(u32));
	md5_transform(ctx->hash, ctx->block);
}