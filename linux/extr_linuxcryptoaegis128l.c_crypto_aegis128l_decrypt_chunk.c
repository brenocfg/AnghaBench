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
union aegis_chunk {int /*<<< orphan*/  const* bytes; union aegis_block* blocks; } ;
union aegis_block {int /*<<< orphan*/  bytes; } ;
typedef  int /*<<< orphan*/  const u8 ;
struct aegis_state {union aegis_block* blocks; } ;

/* Variables and functions */
 unsigned int AEGIS128L_CHUNK_SIZE ; 
 scalar_t__ AEGIS_ALIGNED (int /*<<< orphan*/  const*) ; 
 int AEGIS_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_aegis128l_update_a (struct aegis_state*,union aegis_chunk*) ; 
 int /*<<< orphan*/  crypto_aegis_block_and (union aegis_block*,union aegis_block*) ; 
 int /*<<< orphan*/  crypto_aegis_block_xor (union aegis_block*,union aegis_block*) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void crypto_aegis128l_decrypt_chunk(struct aegis_state *state, u8 *dst,
					   const u8 *src, unsigned int size)
{
	union aegis_chunk tmp;
	union aegis_block *tmp0 = &tmp.blocks[0];
	union aegis_block *tmp1 = &tmp.blocks[1];

	if (AEGIS_ALIGNED(src) && AEGIS_ALIGNED(dst)) {
		while (size >= AEGIS128L_CHUNK_SIZE) {
			union aegis_chunk *dst_blk =
					(union aegis_chunk *)dst;
			const union aegis_chunk *src_blk =
					(const union aegis_chunk *)src;

			*tmp0 = state->blocks[2];
			crypto_aegis_block_and(tmp0, &state->blocks[3]);
			crypto_aegis_block_xor(tmp0, &state->blocks[6]);
			crypto_aegis_block_xor(tmp0, &state->blocks[1]);
			crypto_aegis_block_xor(tmp0, &src_blk->blocks[0]);

			*tmp1 = state->blocks[6];
			crypto_aegis_block_and(tmp1, &state->blocks[7]);
			crypto_aegis_block_xor(tmp1, &state->blocks[5]);
			crypto_aegis_block_xor(tmp1, &state->blocks[2]);
			crypto_aegis_block_xor(tmp1, &src_blk->blocks[1]);

			crypto_aegis128l_update_a(state, &tmp);

			*dst_blk = tmp;

			size -= AEGIS128L_CHUNK_SIZE;
			src += AEGIS128L_CHUNK_SIZE;
			dst += AEGIS128L_CHUNK_SIZE;
		}
	} else {
		while (size >= AEGIS128L_CHUNK_SIZE) {
			*tmp0 = state->blocks[2];
			crypto_aegis_block_and(tmp0, &state->blocks[3]);
			crypto_aegis_block_xor(tmp0, &state->blocks[6]);
			crypto_aegis_block_xor(tmp0, &state->blocks[1]);
			crypto_xor(tmp0->bytes, src + 0 * AEGIS_BLOCK_SIZE,
				   AEGIS_BLOCK_SIZE);

			*tmp1 = state->blocks[6];
			crypto_aegis_block_and(tmp1, &state->blocks[7]);
			crypto_aegis_block_xor(tmp1, &state->blocks[5]);
			crypto_aegis_block_xor(tmp1, &state->blocks[2]);
			crypto_xor(tmp1->bytes, src + 1 * AEGIS_BLOCK_SIZE,
				   AEGIS_BLOCK_SIZE);

			crypto_aegis128l_update_a(state, &tmp);

			memcpy(dst, tmp.bytes, AEGIS128L_CHUNK_SIZE);

			size -= AEGIS128L_CHUNK_SIZE;
			src += AEGIS128L_CHUNK_SIZE;
			dst += AEGIS128L_CHUNK_SIZE;
		}
	}

	if (size > 0) {
		union aegis_chunk msg = {};
		memcpy(msg.bytes, src, size);

		*tmp0 = state->blocks[2];
		crypto_aegis_block_and(tmp0, &state->blocks[3]);
		crypto_aegis_block_xor(tmp0, &state->blocks[6]);
		crypto_aegis_block_xor(tmp0, &state->blocks[1]);
		crypto_aegis_block_xor(&msg.blocks[0], tmp0);

		*tmp1 = state->blocks[6];
		crypto_aegis_block_and(tmp1, &state->blocks[7]);
		crypto_aegis_block_xor(tmp1, &state->blocks[5]);
		crypto_aegis_block_xor(tmp1, &state->blocks[2]);
		crypto_aegis_block_xor(&msg.blocks[1], tmp1);

		memset(msg.bytes + size, 0, AEGIS128L_CHUNK_SIZE - size);

		crypto_aegis128l_update_a(state, &msg);

		memcpy(dst, msg.bytes, size);
	}
}