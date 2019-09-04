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
struct alt_instr {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/ * ALT_REPL_PTR (struct alt_instr*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_alt_insn (struct alt_instr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void patch_alternative(struct alt_instr *alt,
			      __le32 *origptr, __le32 *updptr, int nr_inst)
{
	__le32 *replptr;
	int i;

	replptr = ALT_REPL_PTR(alt);
	for (i = 0; i < nr_inst; i++) {
		u32 insn;

		insn = get_alt_insn(alt, origptr + i, replptr + i);
		updptr[i] = cpu_to_le32(insn);
	}
}