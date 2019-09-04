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
struct morus640_block {int* words; } ;

/* Variables and functions */
 unsigned int MORUS_BLOCK_WORDS ; 
 int rol32 (int,unsigned int) ; 

__attribute__((used)) static void crypto_morus640_round(struct morus640_block *b0,
				  struct morus640_block *b1,
				  struct morus640_block *b2,
				  struct morus640_block *b3,
				  struct morus640_block *b4,
				  const struct morus640_block *m,
				  unsigned int b, unsigned int w)
{
	unsigned int i;
	struct morus640_block tmp;

	for (i = 0; i < MORUS_BLOCK_WORDS; i++) {
		b0->words[i] ^= b1->words[i] & b2->words[i];
		b0->words[i] ^= b3->words[i];
		b0->words[i] ^= m->words[i];
		b0->words[i] = rol32(b0->words[i], b);
	}

	tmp = *b3;
	for (i = 0; i < MORUS_BLOCK_WORDS; i++)
		b3->words[(i + w) % MORUS_BLOCK_WORDS] = tmp.words[i];
}