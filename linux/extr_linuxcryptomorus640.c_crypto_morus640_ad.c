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
struct morus640_state {int dummy; } ;
struct morus640_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ MORUS640_ALIGNED (int /*<<< orphan*/  const*) ; 
 unsigned int MORUS640_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_morus640_load_a (struct morus640_block*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_morus640_load_u (struct morus640_block*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_morus640_update (struct morus640_state*,struct morus640_block*) ; 

__attribute__((used)) static void crypto_morus640_ad(struct morus640_state *state, const u8 *src,
			       unsigned int size)
{
	struct morus640_block m;

	if (MORUS640_ALIGNED(src)) {
		while (size >= MORUS640_BLOCK_SIZE) {
			crypto_morus640_load_a(&m, src);
			crypto_morus640_update(state, &m);

			size -= MORUS640_BLOCK_SIZE;
			src += MORUS640_BLOCK_SIZE;
		}
	} else {
		while (size >= MORUS640_BLOCK_SIZE) {
			crypto_morus640_load_u(&m, src);
			crypto_morus640_update(state, &m);

			size -= MORUS640_BLOCK_SIZE;
			src += MORUS640_BLOCK_SIZE;
		}
	}
}