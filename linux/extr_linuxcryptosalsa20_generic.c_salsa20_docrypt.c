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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int SALSA20_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  salsa20_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void salsa20_docrypt(u32 *state, u8 *dst, const u8 *src,
			    unsigned int bytes)
{
	__le32 stream[SALSA20_BLOCK_SIZE / sizeof(__le32)];

	if (dst != src)
		memcpy(dst, src, bytes);

	while (bytes >= SALSA20_BLOCK_SIZE) {
		salsa20_block(state, stream);
		crypto_xor(dst, (const u8 *)stream, SALSA20_BLOCK_SIZE);
		bytes -= SALSA20_BLOCK_SIZE;
		dst += SALSA20_BLOCK_SIZE;
	}
	if (bytes) {
		salsa20_block(state, stream);
		crypto_xor(dst, (const u8 *)stream, bytes);
	}
}