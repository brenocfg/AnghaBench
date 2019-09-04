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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  HPET_COUNTER ; 
 int MAX_RETRIES ; 
 scalar_t__ SMI_TRESHOLD ; 
 scalar_t__ ULLONG_MAX ; 
 scalar_t__ acpi_pm_read_early () ; 
 scalar_t__ get_cycles () ; 
 int hpet_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 tsc_read_refs(u64 *p, int hpet)
{
	u64 t1, t2;
	int i;

	for (i = 0; i < MAX_RETRIES; i++) {
		t1 = get_cycles();
		if (hpet)
			*p = hpet_readl(HPET_COUNTER) & 0xFFFFFFFF;
		else
			*p = acpi_pm_read_early();
		t2 = get_cycles();
		if ((t2 - t1) < SMI_TRESHOLD)
			return t2;
	}
	return ULLONG_MAX;
}