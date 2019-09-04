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
typedef  union aegis_chunk {int dummy; } aegis_chunk ;
typedef  int /*<<< orphan*/  u8 ;
struct aegis_state {int dummy; } ;

/* Variables and functions */
 unsigned int AEGIS128L_CHUNK_SIZE ; 
 scalar_t__ AEGIS_ALIGNED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_aegis128l_update_a (struct aegis_state*,union aegis_chunk const*) ; 
 int /*<<< orphan*/  crypto_aegis128l_update_u (struct aegis_state*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void crypto_aegis128l_ad(struct aegis_state *state,
				const u8 *src, unsigned int size)
{
	if (AEGIS_ALIGNED(src)) {
		const union aegis_chunk *src_chunk =
				(const union aegis_chunk *)src;

		while (size >= AEGIS128L_CHUNK_SIZE) {
			crypto_aegis128l_update_a(state, src_chunk);

			size -= AEGIS128L_CHUNK_SIZE;
			src_chunk += 1;
		}
	} else {
		while (size >= AEGIS128L_CHUNK_SIZE) {
			crypto_aegis128l_update_u(state, src);

			size -= AEGIS128L_CHUNK_SIZE;
			src += AEGIS128L_CHUNK_SIZE;
		}
	}
}