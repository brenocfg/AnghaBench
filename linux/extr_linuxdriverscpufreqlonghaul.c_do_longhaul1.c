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
struct TYPE_2__ {int ESOFTBF; unsigned int CLOCKMUL; } ;
union msr_bcr2 {int /*<<< orphan*/  val; TYPE_1__ bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FLUSH_CPU_CACHE () ; 
 int /*<<< orphan*/  MSR_VIA_BCR2 ; 
 int /*<<< orphan*/  halt () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_halt () ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_longhaul1(unsigned int mults_index)
{
	union msr_bcr2 bcr2;

	rdmsrl(MSR_VIA_BCR2, bcr2.val);
	/* Enable software clock multiplier */
	bcr2.bits.ESOFTBF = 1;
	bcr2.bits.CLOCKMUL = mults_index & 0xff;

	/* Sync to timer tick */
	safe_halt();
	/* Change frequency on next halt or sleep */
	wrmsrl(MSR_VIA_BCR2, bcr2.val);
	/* Invoke transition */
	ACPI_FLUSH_CPU_CACHE();
	halt();

	/* Disable software clock multiplier */
	local_irq_disable();
	rdmsrl(MSR_VIA_BCR2, bcr2.val);
	bcr2.bits.ESOFTBF = 0;
	wrmsrl(MSR_VIA_BCR2, bcr2.val);
}