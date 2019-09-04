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
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crypto_morus640_store_u(u8 *dst, const struct morus640_block *src)
{
	unsigned int i;
	for (i = 0; i < MORUS_BLOCK_WORDS; i++) {
		put_unaligned_le32(src->words[i], dst);
		dst += MORUS640_WORD_SIZE;
	}
}