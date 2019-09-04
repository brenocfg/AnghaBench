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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 unsigned int CHACHA20_BLOCK_SIZE ; 
 int CHACHA20_BLOCK_WORDS ; 
 int /*<<< orphan*/  chacha20_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void chacha20_docrypt(u32 *state, u8 *dst, const u8 *src,
			     unsigned int bytes)
{
	u32 stream[CHACHA20_BLOCK_WORDS];

	if (dst != src)
		memcpy(dst, src, bytes);

	while (bytes >= CHACHA20_BLOCK_SIZE) {
		chacha20_block(state, stream);
		crypto_xor(dst, (const u8 *)stream, CHACHA20_BLOCK_SIZE);
		bytes -= CHACHA20_BLOCK_SIZE;
		dst += CHACHA20_BLOCK_SIZE;
	}
	if (bytes) {
		chacha20_block(state, stream);
		crypto_xor(dst, (const u8 *)stream, bytes);
	}
}