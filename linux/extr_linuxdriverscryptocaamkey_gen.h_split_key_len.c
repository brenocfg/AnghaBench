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
typedef  int u8 ;
typedef  size_t u32 ;

/* Variables and functions */
 size_t OP_ALG_ALGSEL_SHIFT ; 
 size_t OP_ALG_ALGSEL_SUBMASK ; 

__attribute__((used)) static inline u32 split_key_len(u32 hash)
{
	/* Sizes for MDHA pads (*not* keys): MD5, SHA1, 224, 256, 384, 512 */
	static const u8 mdpadlen[] = { 16, 20, 32, 32, 64, 64 };
	u32 idx;

	idx = (hash & OP_ALG_ALGSEL_SUBMASK) >> OP_ALG_ALGSEL_SHIFT;

	return (u32)(mdpadlen[idx] * 2);
}