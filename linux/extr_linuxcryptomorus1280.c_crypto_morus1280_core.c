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
struct morus1280_state {TYPE_1__* s; } ;
struct morus1280_block {int* words; } ;
struct TYPE_2__ {int* words; } ;

/* Variables and functions */
 unsigned int MORUS_BLOCK_WORDS ; 

__attribute__((used)) static void crypto_morus1280_core(const struct morus1280_state *state,
				  struct morus1280_block *blk)
{
	unsigned int i;

	for (i = 0; i < MORUS_BLOCK_WORDS; i++)
		blk->words[(i + 3) % MORUS_BLOCK_WORDS] ^= state->s[1].words[i];

        for (i = 0; i < MORUS_BLOCK_WORDS; i++) {
		blk->words[i] ^= state->s[0].words[i];
		blk->words[i] ^= state->s[2].words[i] & state->s[3].words[i];
	}
}