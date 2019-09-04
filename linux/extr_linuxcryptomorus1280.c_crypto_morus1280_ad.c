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
struct morus1280_state {int dummy; } ;
struct morus1280_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ MORUS1280_ALIGNED (int /*<<< orphan*/  const*) ; 
 unsigned int MORUS1280_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_morus1280_load_a (struct morus1280_block*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_morus1280_load_u (struct morus1280_block*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_morus1280_update (struct morus1280_state*,struct morus1280_block*) ; 

__attribute__((used)) static void crypto_morus1280_ad(struct morus1280_state *state, const u8 *src,
				unsigned int size)
{
	struct morus1280_block m;

	if (MORUS1280_ALIGNED(src)) {
		while (size >= MORUS1280_BLOCK_SIZE) {
			crypto_morus1280_load_a(&m, src);
			crypto_morus1280_update(state, &m);

			size -= MORUS1280_BLOCK_SIZE;
			src += MORUS1280_BLOCK_SIZE;
		}
	} else {
		while (size >= MORUS1280_BLOCK_SIZE) {
			crypto_morus1280_load_u(&m, src);
			crypto_morus1280_update(state, &m);

			size -= MORUS1280_BLOCK_SIZE;
			src += MORUS1280_BLOCK_SIZE;
		}
	}
}