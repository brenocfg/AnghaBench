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
typedef  int /*<<< orphan*/  const u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int CHACHA20_BLOCK_SIZE ; 
 int /*<<< orphan*/  chacha20_4block_xor_neon (scalar_t__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  chacha20_block_xor_neon (scalar_t__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void chacha20_doneon(u32 *state, u8 *dst, const u8 *src,
			    unsigned int bytes)
{
	u8 buf[CHACHA20_BLOCK_SIZE];

	while (bytes >= CHACHA20_BLOCK_SIZE * 4) {
		kernel_neon_begin();
		chacha20_4block_xor_neon(state, dst, src);
		kernel_neon_end();
		bytes -= CHACHA20_BLOCK_SIZE * 4;
		src += CHACHA20_BLOCK_SIZE * 4;
		dst += CHACHA20_BLOCK_SIZE * 4;
		state[12] += 4;
	}

	if (!bytes)
		return;

	kernel_neon_begin();
	while (bytes >= CHACHA20_BLOCK_SIZE) {
		chacha20_block_xor_neon(state, dst, src);
		bytes -= CHACHA20_BLOCK_SIZE;
		src += CHACHA20_BLOCK_SIZE;
		dst += CHACHA20_BLOCK_SIZE;
		state[12]++;
	}
	if (bytes) {
		memcpy(buf, src, bytes);
		chacha20_block_xor_neon(state, buf, buf);
		memcpy(dst, buf, bytes);
	}
	kernel_neon_end();
}