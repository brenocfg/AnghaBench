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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct drxd_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHUNK_SIZE ; 
 scalar_t__ write_chunk (struct drxd_state*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int WriteBlock(struct drxd_state *state,
		      u32 Address, u16 BlockSize, u8 *pBlock, u8 Flags)
{
	while (BlockSize > 0) {
		u16 Chunk = BlockSize > CHUNK_SIZE ? CHUNK_SIZE : BlockSize;

		if (write_chunk(state, Address, pBlock, Chunk, Flags) < 0)
			return -1;
		pBlock += Chunk;
		Address += (Chunk >> 1);
		BlockSize -= Chunk;
	}
	return 0;
}