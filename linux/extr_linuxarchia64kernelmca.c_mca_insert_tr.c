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
typedef  int u64 ;
struct ia64_tr_entry {int pte; int rr; int itir; int /*<<< orphan*/  ifa; } ;

/* Variables and functions */
 int IA64_TR_ALLOC_BASE ; 
 int IA64_TR_ALLOC_MAX ; 
 unsigned long ia64_clear_ic () ; 
 int ia64_get_rr (int /*<<< orphan*/ ) ; 
 struct ia64_tr_entry** ia64_idtrs ; 
 int /*<<< orphan*/  ia64_itr (int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ia64_ptr (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ia64_set_psr (unsigned long) ; 
 int /*<<< orphan*/  ia64_set_rr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ia64_srlz_d () ; 
 int /*<<< orphan*/  ia64_srlz_i () ; 
 int smp_processor_id () ; 

__attribute__((used)) static void mca_insert_tr(u64 iord)
{

	int i;
	u64 old_rr;
	struct ia64_tr_entry *p;
	unsigned long psr;
	int cpu = smp_processor_id();

	if (!ia64_idtrs[cpu])
		return;

	psr = ia64_clear_ic();
	for (i = IA64_TR_ALLOC_BASE; i < IA64_TR_ALLOC_MAX; i++) {
		p = ia64_idtrs[cpu] + (iord - 1) * IA64_TR_ALLOC_MAX;
		if (p->pte & 0x1) {
			old_rr = ia64_get_rr(p->ifa);
			if (old_rr != p->rr) {
				ia64_set_rr(p->ifa, p->rr);
				ia64_srlz_d();
			}
			ia64_ptr(iord, p->ifa, p->itir >> 2);
			ia64_srlz_i();
			if (iord & 0x1) {
				ia64_itr(0x1, i, p->ifa, p->pte, p->itir >> 2);
				ia64_srlz_i();
			}
			if (iord & 0x2) {
				ia64_itr(0x2, i, p->ifa, p->pte, p->itir >> 2);
				ia64_srlz_i();
			}
			if (old_rr != p->rr) {
				ia64_set_rr(p->ifa, old_rr);
				ia64_srlz_d();
			}
		}
	}
	ia64_set_psr(psr);
}