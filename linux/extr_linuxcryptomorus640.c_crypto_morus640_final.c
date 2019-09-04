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
typedef  int u64 ;
struct morus640_state {TYPE_1__* s; } ;
struct morus640_block {void** words; } ;
struct TYPE_2__ {int /*<<< orphan*/ * words; } ;

/* Variables and functions */
 unsigned int MORUS_BLOCK_WORDS ; 
 int /*<<< orphan*/  crypto_morus640_core (struct morus640_state*,struct morus640_block*) ; 
 int /*<<< orphan*/  crypto_morus640_update (struct morus640_state*,struct morus640_block*) ; 
 void* lower_32_bits (int) ; 
 void* upper_32_bits (int) ; 

__attribute__((used)) static void crypto_morus640_final(struct morus640_state *state,
				  struct morus640_block *tag_xor,
				  u64 assoclen, u64 cryptlen)
{
	struct morus640_block tmp;
	unsigned int i;

	tmp.words[0] = lower_32_bits(assoclen * 8);
	tmp.words[1] = upper_32_bits(assoclen * 8);
	tmp.words[2] = lower_32_bits(cryptlen * 8);
	tmp.words[3] = upper_32_bits(cryptlen * 8);

	for (i = 0; i < MORUS_BLOCK_WORDS; i++)
		state->s[4].words[i] ^= state->s[0].words[i];

	for (i = 0; i < 10; i++)
		crypto_morus640_update(state, &tmp);

	crypto_morus640_core(state, tag_xor);
}