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
 int _PAGE_PRESENT ; 
 int _PAGE_PRESENT_SHIFT ; 
 int _PAGE_WRITE ; 
 int /*<<< orphan*/  iPTE_LW (int /*<<< orphan*/ **,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_andi (int /*<<< orphan*/ **,int,int,int) ; 
 int /*<<< orphan*/  uasm_i_nop (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_srl (int /*<<< orphan*/ **,int,int,int) ; 
 int /*<<< orphan*/  uasm_i_xori (int /*<<< orphan*/ **,int,int,int) ; 
 int /*<<< orphan*/  uasm_il_bnez (int /*<<< orphan*/ **,struct uasm_reloc**,int,int) ; 

__attribute__((used)) static void
build_pte_writable(u32 **p, struct uasm_reloc **r,
		   unsigned int pte, unsigned int ptr, int scratch,
		   enum label_id lid)
{
	int t = scratch >= 0 ? scratch : pte;
	int cur = pte;

	if (_PAGE_PRESENT_SHIFT) {
		uasm_i_srl(p, t, cur, _PAGE_PRESENT_SHIFT);
		cur = t;
	}
	uasm_i_andi(p, t, cur,
		    (_PAGE_PRESENT | _PAGE_WRITE) >> _PAGE_PRESENT_SHIFT);
	uasm_i_xori(p, t, t,
		    (_PAGE_PRESENT | _PAGE_WRITE) >> _PAGE_PRESENT_SHIFT);
	uasm_il_bnez(p, r, t, lid);
	if (pte == t)
		/* You lose the SMP race :-(*/
		iPTE_LW(p, pte, ptr);
	else
		uasm_i_nop(p);
}