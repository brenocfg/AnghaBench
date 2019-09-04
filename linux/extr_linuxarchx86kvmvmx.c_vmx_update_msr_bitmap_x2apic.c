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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_EOI ; 
 int /*<<< orphan*/  APIC_SELF_IPI ; 
 int /*<<< orphan*/  APIC_TASKPRI ; 
 int /*<<< orphan*/  APIC_TMCCT ; 
 int BITS_PER_LONG ; 
 int MSR_BITMAP_MODE_X2APIC ; 
 int MSR_BITMAP_MODE_X2APIC_APICV ; 
 int /*<<< orphan*/  MSR_TYPE_R ; 
 int /*<<< orphan*/  MSR_TYPE_RW ; 
 int /*<<< orphan*/  MSR_TYPE_W ; 
 int /*<<< orphan*/  X2APIC_MSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_disable_intercept_for_msr (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_enable_intercept_for_msr (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_update_msr_bitmap_x2apic(unsigned long *msr_bitmap,
					 u8 mode)
{
	int msr;

	for (msr = 0x800; msr <= 0x8ff; msr += BITS_PER_LONG) {
		unsigned word = msr / BITS_PER_LONG;
		msr_bitmap[word] = (mode & MSR_BITMAP_MODE_X2APIC_APICV) ? 0 : ~0;
		msr_bitmap[word + (0x800 / sizeof(long))] = ~0;
	}

	if (mode & MSR_BITMAP_MODE_X2APIC) {
		/*
		 * TPR reads and writes can be virtualized even if virtual interrupt
		 * delivery is not in use.
		 */
		vmx_disable_intercept_for_msr(msr_bitmap, X2APIC_MSR(APIC_TASKPRI), MSR_TYPE_RW);
		if (mode & MSR_BITMAP_MODE_X2APIC_APICV) {
			vmx_enable_intercept_for_msr(msr_bitmap, X2APIC_MSR(APIC_TMCCT), MSR_TYPE_R);
			vmx_disable_intercept_for_msr(msr_bitmap, X2APIC_MSR(APIC_EOI), MSR_TYPE_W);
			vmx_disable_intercept_for_msr(msr_bitmap, X2APIC_MSR(APIC_SELF_IPI), MSR_TYPE_W);
		}
	}
}