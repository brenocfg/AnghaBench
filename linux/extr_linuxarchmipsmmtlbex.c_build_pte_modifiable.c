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
typedef  enum label_id { ____Placeholder_label_id } label_id ;

/* Variables and functions */
 int /*<<< orphan*/  _PAGE_WRITE ; 
 int /*<<< orphan*/  _PAGE_WRITE_SHIFT ; 
 int /*<<< orphan*/  iPTE_LW (int /*<<< orphan*/ **,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_andi (int /*<<< orphan*/ **,int,int,int) ; 
 int /*<<< orphan*/  uasm_i_nop (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_srl (int /*<<< orphan*/ **,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_il_bbit0 (int /*<<< orphan*/ **,struct uasm_reloc**,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uasm_il_beqz (int /*<<< orphan*/ **,struct uasm_reloc**,int,int) ; 
 scalar_t__ use_bbit_insns () ; 

__attribute__((used)) static void
build_pte_modifiable(u32 **p, struct uasm_reloc **r,
		     unsigned int pte, unsigned int ptr, int scratch,
		     enum label_id lid)
{
	if (use_bbit_insns()) {
		uasm_il_bbit0(p, r, pte, ilog2(_PAGE_WRITE), lid);
		uasm_i_nop(p);
	} else {
		int t = scratch >= 0 ? scratch : pte;
		uasm_i_srl(p, t, pte, _PAGE_WRITE_SHIFT);
		uasm_i_andi(p, t, t, 1);
		uasm_il_beqz(p, r, t, lid);
		if (pte == t)
			/* You lose the SMP race :-(*/
			iPTE_LW(p, pte, ptr);
	}
}