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
struct scatterlist {int dummy; } ;
struct scatter_walk {int dummy; } ;
struct aegis_state {int dummy; } ;
struct aegis_block {int /*<<< orphan*/  const* bytes; } ;

/* Variables and functions */
 unsigned int AEGIS128_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_aegis128_aesni_ad (struct aegis_state*,unsigned int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_advance (struct scatter_walk*,unsigned int) ; 
 unsigned int scatterwalk_clamp (struct scatter_walk*,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_done (struct scatter_walk*,int /*<<< orphan*/ ,unsigned int) ; 
 void* scatterwalk_map (struct scatter_walk*) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,struct scatterlist*) ; 
 int /*<<< orphan*/  scatterwalk_unmap (void*) ; 

__attribute__((used)) static void crypto_aegis128_aesni_process_ad(
		struct aegis_state *state, struct scatterlist *sg_src,
		unsigned int assoclen)
{
	struct scatter_walk walk;
	struct aegis_block buf;
	unsigned int pos = 0;

	scatterwalk_start(&walk, sg_src);
	while (assoclen != 0) {
		unsigned int size = scatterwalk_clamp(&walk, assoclen);
		unsigned int left = size;
		void *mapped = scatterwalk_map(&walk);
		const u8 *src = (const u8 *)mapped;

		if (pos + size >= AEGIS128_BLOCK_SIZE) {
			if (pos > 0) {
				unsigned int fill = AEGIS128_BLOCK_SIZE - pos;
				memcpy(buf.bytes + pos, src, fill);
				crypto_aegis128_aesni_ad(state,
							 AEGIS128_BLOCK_SIZE,
							 buf.bytes);
				pos = 0;
				left -= fill;
				src += fill;
			}

			crypto_aegis128_aesni_ad(state, left, src);

			src += left & ~(AEGIS128_BLOCK_SIZE - 1);
			left &= AEGIS128_BLOCK_SIZE - 1;
		}

		memcpy(buf.bytes + pos, src, left);
		pos += left;
		assoclen -= size;

		scatterwalk_unmap(mapped);
		scatterwalk_advance(&walk, size);
		scatterwalk_done(&walk, 0, assoclen);
	}

	if (pos > 0) {
		memset(buf.bytes + pos, 0, AEGIS128_BLOCK_SIZE - pos);
		crypto_aegis128_aesni_ad(state, AEGIS128_BLOCK_SIZE, buf.bytes);
	}
}