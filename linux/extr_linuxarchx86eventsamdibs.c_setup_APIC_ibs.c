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

/* Variables and functions */
 int /*<<< orphan*/  APIC_EILVT_MSG_NMI ; 
 int get_ibs_lvt_offset () ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_APIC_eilvt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void setup_APIC_ibs(void)
{
	int offset;

	offset = get_ibs_lvt_offset();
	if (offset < 0)
		goto failed;

	if (!setup_APIC_eilvt(offset, 0, APIC_EILVT_MSG_NMI, 0))
		return;
failed:
	pr_warn("perf: IBS APIC setup failed on cpu #%d\n",
		smp_processor_id());
}