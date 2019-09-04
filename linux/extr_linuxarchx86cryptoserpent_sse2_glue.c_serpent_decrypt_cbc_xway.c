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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u128 ;

/* Variables and functions */
 int SERPENT_PARALLEL_BLOCKS ; 
 int /*<<< orphan*/  serpent_dec_blk_xway (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void serpent_decrypt_cbc_xway(void *ctx, u128 *dst, const u128 *src)
{
	u128 ivs[SERPENT_PARALLEL_BLOCKS - 1];
	unsigned int j;

	for (j = 0; j < SERPENT_PARALLEL_BLOCKS - 1; j++)
		ivs[j] = src[j];

	serpent_dec_blk_xway(ctx, (u8 *)dst, (u8 *)src);

	for (j = 0; j < SERPENT_PARALLEL_BLOCKS - 1; j++)
		u128_xor(dst + (j + 1), dst + (j + 1), ivs + j);
}