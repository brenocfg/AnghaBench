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
typedef  int /*<<< orphan*/  u32 ;
struct uasm_reloc {int dummy; } ;
struct uasm_label {int dummy; } ;
struct cache_desc {unsigned int ways; unsigned int waybit; int flags; unsigned int const linesz; } ;

/* Variables and functions */
 scalar_t__ CKSEG0 ; 
 int MIPS_CACHE_NOT_PRESENT ; 
 int /*<<< orphan*/  UASM_i_LA (int /*<<< orphan*/ **,int /*<<< orphan*/ ,long) ; 
 scalar_t__ cpu_has_mips_r6 ; 
 int /*<<< orphan*/  t0 ; 
 int /*<<< orphan*/  t1 ; 
 int /*<<< orphan*/  uasm_build_label (struct uasm_label**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uasm_i_addiu (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  uasm_i_cache (int /*<<< orphan*/ **,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_nop (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_il_bne (int /*<<< orphan*/ **,struct uasm_reloc**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cps_gen_cache_routine(u32 **pp, struct uasm_label **pl,
				  struct uasm_reloc **pr,
				  const struct cache_desc *cache,
				  unsigned op, int lbl)
{
	unsigned cache_size = cache->ways << cache->waybit;
	unsigned i;
	const unsigned unroll_lines = 32;

	/* If the cache isn't present this function has it easy */
	if (cache->flags & MIPS_CACHE_NOT_PRESENT)
		return;

	/* Load base address */
	UASM_i_LA(pp, t0, (long)CKSEG0);

	/* Calculate end address */
	if (cache_size < 0x8000)
		uasm_i_addiu(pp, t1, t0, cache_size);
	else
		UASM_i_LA(pp, t1, (long)(CKSEG0 + cache_size));

	/* Start of cache op loop */
	uasm_build_label(pl, *pp, lbl);

	/* Generate the cache ops */
	for (i = 0; i < unroll_lines; i++) {
		if (cpu_has_mips_r6) {
			uasm_i_cache(pp, op, 0, t0);
			uasm_i_addiu(pp, t0, t0, cache->linesz);
		} else {
			uasm_i_cache(pp, op, i * cache->linesz, t0);
		}
	}

	if (!cpu_has_mips_r6)
		/* Update the base address */
		uasm_i_addiu(pp, t0, t0, unroll_lines * cache->linesz);

	/* Loop if we haven't reached the end address yet */
	uasm_il_bne(pp, pr, t0, t1, lbl);
	uasm_i_nop(pp);
}