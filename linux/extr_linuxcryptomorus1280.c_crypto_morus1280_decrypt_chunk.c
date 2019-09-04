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
union morus1280_block_in {int /*<<< orphan*/  const* bytes; } ;
typedef  int /*<<< orphan*/  const u8 ;
struct morus1280_state {int dummy; } ;
struct morus1280_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ MORUS1280_ALIGNED (int /*<<< orphan*/  const*) ; 
 unsigned int MORUS1280_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_morus1280_core (struct morus1280_state*,struct morus1280_block*) ; 
 int /*<<< orphan*/  crypto_morus1280_load_a (struct morus1280_block*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_morus1280_load_u (struct morus1280_block*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_morus1280_store_a (int /*<<< orphan*/  const*,struct morus1280_block*) ; 
 int /*<<< orphan*/  crypto_morus1280_store_u (int /*<<< orphan*/  const*,struct morus1280_block*) ; 
 int /*<<< orphan*/  crypto_morus1280_update (struct morus1280_state*,struct morus1280_block*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void crypto_morus1280_decrypt_chunk(struct morus1280_state *state,
					   u8 *dst, const u8 *src,
					   unsigned int size)
{
	struct morus1280_block m;

	if (MORUS1280_ALIGNED(src) && MORUS1280_ALIGNED(dst)) {
		while (size >= MORUS1280_BLOCK_SIZE) {
			crypto_morus1280_load_a(&m, src);
			crypto_morus1280_core(state, &m);
			crypto_morus1280_store_a(dst, &m);
			crypto_morus1280_update(state, &m);

			src += MORUS1280_BLOCK_SIZE;
			dst += MORUS1280_BLOCK_SIZE;
			size -= MORUS1280_BLOCK_SIZE;
		}
	} else {
		while (size >= MORUS1280_BLOCK_SIZE) {
			crypto_morus1280_load_u(&m, src);
			crypto_morus1280_core(state, &m);
			crypto_morus1280_store_u(dst, &m);
			crypto_morus1280_update(state, &m);

			src += MORUS1280_BLOCK_SIZE;
			dst += MORUS1280_BLOCK_SIZE;
			size -= MORUS1280_BLOCK_SIZE;
		}
	}

	if (size > 0) {
		union morus1280_block_in tail;

		memcpy(tail.bytes, src, size);
		memset(tail.bytes + size, 0, MORUS1280_BLOCK_SIZE - size);

		crypto_morus1280_load_a(&m, tail.bytes);
		crypto_morus1280_core(state, &m);
		crypto_morus1280_store_a(tail.bytes, &m);
		memset(tail.bytes + size, 0, MORUS1280_BLOCK_SIZE - size);
		crypto_morus1280_load_a(&m, tail.bytes);
		crypto_morus1280_update(state, &m);

		memcpy(dst, tail.bytes, size);
	}
}