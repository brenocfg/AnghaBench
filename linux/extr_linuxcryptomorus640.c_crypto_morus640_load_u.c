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
struct morus640_block {int /*<<< orphan*/ * words; } ;

/* Variables and functions */
 int /*<<< orphan*/  MORUS640_WORD_SIZE ; 
 unsigned int MORUS_BLOCK_WORDS ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void crypto_morus640_load_u(struct morus640_block *dst, const u8 *src)
{
	unsigned int i;
	for (i = 0; i < MORUS_BLOCK_WORDS; i++) {
		dst->words[i] = get_unaligned_le32(src);
		src += MORUS640_WORD_SIZE;
	}
}