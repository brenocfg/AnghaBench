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
union morus640_block_in {int /*<<< orphan*/  const* bytes; } ;
typedef  int /*<<< orphan*/  const u8 ;
struct morus640_state {int dummy; } ;
struct morus640_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ MORUS640_ALIGNED (int /*<<< orphan*/  const*) ; 
 unsigned int MORUS640_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_morus640_core (struct morus640_state*,struct morus640_block*) ; 
 int /*<<< orphan*/  crypto_morus640_load_a (struct morus640_block*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_morus640_load_u (struct morus640_block*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_morus640_store_a (int /*<<< orphan*/  const*,struct morus640_block*) ; 
 int /*<<< orphan*/  crypto_morus640_store_u (int /*<<< orphan*/  const*,struct morus640_block*) ; 
 int /*<<< orphan*/  crypto_morus640_update (struct morus640_state*,struct morus640_block*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void crypto_morus640_encrypt_chunk(struct morus640_state *state, u8 *dst,
					  const u8 *src, unsigned int size)
{
	struct morus640_block c, m;

	if (MORUS640_ALIGNED(src) && MORUS640_ALIGNED(dst)) {
		while (size >= MORUS640_BLOCK_SIZE) {
			crypto_morus640_load_a(&m, src);
			c = m;
			crypto_morus640_core(state, &c);
			crypto_morus640_store_a(dst, &c);
			crypto_morus640_update(state, &m);

			src += MORUS640_BLOCK_SIZE;
			dst += MORUS640_BLOCK_SIZE;
			size -= MORUS640_BLOCK_SIZE;
		}
	} else {
		while (size >= MORUS640_BLOCK_SIZE) {
			crypto_morus640_load_u(&m, src);
			c = m;
			crypto_morus640_core(state, &c);
			crypto_morus640_store_u(dst, &c);
			crypto_morus640_update(state, &m);

			src += MORUS640_BLOCK_SIZE;
			dst += MORUS640_BLOCK_SIZE;
			size -= MORUS640_BLOCK_SIZE;
		}
	}

	if (size > 0) {
		union morus640_block_in tail;

		memcpy(tail.bytes, src, size);
		memset(tail.bytes + size, 0, MORUS640_BLOCK_SIZE - size);

		crypto_morus640_load_a(&m, tail.bytes);
		c = m;
		crypto_morus640_core(state, &c);
		crypto_morus640_store_a(tail.bytes, &c);
		crypto_morus640_update(state, &m);

		memcpy(dst, tail.bytes, size);
	}
}