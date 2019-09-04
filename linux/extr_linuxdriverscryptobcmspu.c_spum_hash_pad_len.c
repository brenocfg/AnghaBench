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
typedef  int /*<<< orphan*/  u64 ;
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;
typedef  enum hash_mode { ____Placeholder_hash_mode } hash_mode ;
typedef  enum hash_alg { ____Placeholder_hash_alg } hash_alg ;

/* Variables and functions */
 int HASH_ALG_AES ; 
 int HASH_ALG_SHA384 ; 
 int HASH_ALG_SHA512 ; 
 int HASH_MODE_XCBC ; 

u16 spum_hash_pad_len(enum hash_alg hash_alg, enum hash_mode hash_mode,
		      u32 chunksize, u16 hash_block_size)
{
	unsigned int length_len;
	unsigned int used_space_last_block;
	int hash_pad_len;

	/* AES-XCBC hash requires just padding to next block boundary */
	if ((hash_alg == HASH_ALG_AES) && (hash_mode == HASH_MODE_XCBC)) {
		used_space_last_block = chunksize % hash_block_size;
		hash_pad_len = hash_block_size - used_space_last_block;
		if (hash_pad_len >= hash_block_size)
			hash_pad_len -= hash_block_size;
		return hash_pad_len;
	}

	used_space_last_block = chunksize % hash_block_size + 1;
	if ((hash_alg == HASH_ALG_SHA384) || (hash_alg == HASH_ALG_SHA512))
		length_len = 2 * sizeof(u64);
	else
		length_len = sizeof(u64);

	used_space_last_block += length_len;
	hash_pad_len = hash_block_size - used_space_last_block;
	if (hash_pad_len < 0)
		hash_pad_len += hash_block_size;

	hash_pad_len += 1 + length_len;
	return hash_pad_len;
}