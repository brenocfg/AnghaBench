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
struct morus1280_state {TYPE_1__* s; } ;
struct morus1280_block {int* words; } ;
struct TYPE_2__ {int /*<<< orphan*/ * words; } ;

/* Variables and functions */
 unsigned int MORUS_BLOCK_WORDS ; 
 int /*<<< orphan*/  crypto_morus1280_core (struct morus1280_state*,struct morus1280_block*) ; 
 int /*<<< orphan*/  crypto_morus1280_update (struct morus1280_state*,struct morus1280_block*) ; 

__attribute__((used)) static void crypto_morus1280_final(struct morus1280_state *state,
				   struct morus1280_block *tag_xor,
				   u64 assoclen, u64 cryptlen)
{
	struct morus1280_block tmp;
	unsigned int i;

	tmp.words[0] = assoclen * 8;
	tmp.words[1] = cryptlen * 8;
	tmp.words[2] = 0;
	tmp.words[3] = 0;

	for (i = 0; i < MORUS_BLOCK_WORDS; i++)
		state->s[4].words[i] ^= state->s[0].words[i];

	for (i = 0; i < 10; i++)
		crypto_morus1280_update(state, &tmp);

	crypto_morus1280_core(state, tag_xor);
}