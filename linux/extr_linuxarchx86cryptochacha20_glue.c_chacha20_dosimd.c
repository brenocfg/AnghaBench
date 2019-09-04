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
 int /*<<< orphan*/  chacha20_4block_xor_ssse3 (scalar_t__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  chacha20_block_xor_ssse3 (scalar_t__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void chacha20_dosimd(u32 *state, u8 *dst, const u8 *src,
			    unsigned int bytes)
{
	u8 buf[CHACHA20_BLOCK_SIZE];

#ifdef CONFIG_AS_AVX2
	if (chacha20_use_avx2) {
		while (bytes >= CHACHA20_BLOCK_SIZE * 8) {
			chacha20_8block_xor_avx2(state, dst, src);
			bytes -= CHACHA20_BLOCK_SIZE * 8;
			src += CHACHA20_BLOCK_SIZE * 8;
			dst += CHACHA20_BLOCK_SIZE * 8;
			state[12] += 8;
		}
	}
#endif
	while (bytes >= CHACHA20_BLOCK_SIZE * 4) {
		chacha20_4block_xor_ssse3(state, dst, src);
		bytes -= CHACHA20_BLOCK_SIZE * 4;
		src += CHACHA20_BLOCK_SIZE * 4;
		dst += CHACHA20_BLOCK_SIZE * 4;
		state[12] += 4;
	}
	while (bytes >= CHACHA20_BLOCK_SIZE) {
		chacha20_block_xor_ssse3(state, dst, src);
		bytes -= CHACHA20_BLOCK_SIZE;
		src += CHACHA20_BLOCK_SIZE;
		dst += CHACHA20_BLOCK_SIZE;
		state[12]++;
	}
	if (bytes) {
		memcpy(buf, src, bytes);
		chacha20_block_xor_ssse3(state, buf, buf);
		memcpy(dst, buf, bytes);
	}
}