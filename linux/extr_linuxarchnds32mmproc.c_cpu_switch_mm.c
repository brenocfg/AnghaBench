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
struct TYPE_2__ {unsigned long id; } ;
struct mm_struct {int /*<<< orphan*/  pgd; TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDS32_SR_L1_PPTB ; 
 int /*<<< orphan*/  NDS32_SR_TLB_MISC ; 
 unsigned long TLB_MISC_mskCID ; 
 unsigned long __nds32__mfsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nds32__mtsr_dsb (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nds32__mtsr_isb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 

void cpu_switch_mm(struct mm_struct *mm)
{
	unsigned long cid;
	cid = __nds32__mfsr(NDS32_SR_TLB_MISC);
	cid = (cid & ~TLB_MISC_mskCID) | mm->context.id;
	__nds32__mtsr_dsb(cid, NDS32_SR_TLB_MISC);
	__nds32__mtsr_isb(__pa(mm->pgd), NDS32_SR_L1_PPTB);
}