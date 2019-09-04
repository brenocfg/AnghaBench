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
struct morus1280_state {int dummy; } ;
struct morus1280_glue_ops {int /*<<< orphan*/  (* ad ) (struct morus1280_state*,int /*<<< orphan*/  const*,unsigned int) ;} ;
struct morus1280_block {int /*<<< orphan*/  const* bytes; } ;

/* Variables and functions */
 unsigned int MORUS1280_BLOCK_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_advance (struct scatter_walk*,unsigned int) ; 
 unsigned int scatterwalk_clamp (struct scatter_walk*,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_done (struct scatter_walk*,int /*<<< orphan*/ ,unsigned int) ; 
 void* scatterwalk_map (struct scatter_walk*) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,struct scatterlist*) ; 
 int /*<<< orphan*/  scatterwalk_unmap (void*) ; 
 int /*<<< orphan*/  stub1 (struct morus1280_state*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct morus1280_state*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (struct morus1280_state*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void crypto_morus1280_glue_process_ad(
		struct morus1280_state *state,
		const struct morus1280_glue_ops *ops,
		struct scatterlist *sg_src, unsigned int assoclen)
{
	struct scatter_walk walk;
	struct morus1280_block buf;
	unsigned int pos = 0;

	scatterwalk_start(&walk, sg_src);
	while (assoclen != 0) {
		unsigned int size = scatterwalk_clamp(&walk, assoclen);
		unsigned int left = size;
		void *mapped = scatterwalk_map(&walk);
		const u8 *src = (const u8 *)mapped;

		if (pos + size >= MORUS1280_BLOCK_SIZE) {
			if (pos > 0) {
				unsigned int fill = MORUS1280_BLOCK_SIZE - pos;
				memcpy(buf.bytes + pos, src, fill);
				ops->ad(state, buf.bytes, MORUS1280_BLOCK_SIZE);
				pos = 0;
				left -= fill;
				src += fill;
			}

			ops->ad(state, src, left);
			src += left & ~(MORUS1280_BLOCK_SIZE - 1);
			left &= MORUS1280_BLOCK_SIZE - 1;
		}

		memcpy(buf.bytes + pos, src, left);

		pos += left;
		assoclen -= size;
		scatterwalk_unmap(mapped);
		scatterwalk_advance(&walk, size);
		scatterwalk_done(&walk, 0, assoclen);
	}

	if (pos > 0) {
		memset(buf.bytes + pos, 0, MORUS1280_BLOCK_SIZE - pos);
		ops->ad(state, buf.bytes, MORUS1280_BLOCK_SIZE);
	}
}