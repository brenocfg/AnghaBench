#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  asce; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDTE_GLOBAL ; 
 int IDTE_GUEST_ASCE ; 
 int IDTE_NODAT ; 
 scalar_t__ MACHINE_HAS_IDTE ; 
 scalar_t__ MACHINE_HAS_TLB_GUEST ; 
 int /*<<< orphan*/  __pmdp_csp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pudp_idte (unsigned long,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pudp_idte_global(struct mm_struct *mm,
				    unsigned long addr, pud_t *pudp)
{
	if (MACHINE_HAS_TLB_GUEST)
		__pudp_idte(addr, pudp, IDTE_NODAT | IDTE_GUEST_ASCE,
			    mm->context.asce, IDTE_GLOBAL);
	else if (MACHINE_HAS_IDTE)
		__pudp_idte(addr, pudp, 0, 0, IDTE_GLOBAL);
	else
		/*
		 * Invalid bit position is the same for pmd and pud, so we can
		 * re-use _pmd_csp() here
		 */
		__pmdp_csp((pmd_t *) pudp);
}