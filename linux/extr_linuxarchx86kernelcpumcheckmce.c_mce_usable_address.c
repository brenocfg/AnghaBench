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
struct mce {int status; int /*<<< orphan*/  misc; } ;
struct TYPE_2__ {scalar_t__ x86_vendor; } ;

/* Variables and functions */
 scalar_t__ MCI_MISC_ADDR_LSB (int /*<<< orphan*/ ) ; 
 scalar_t__ MCI_MISC_ADDR_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MCI_MISC_ADDR_PHYS ; 
 int MCI_STATUS_ADDRV ; 
 int MCI_STATUS_MISCV ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 TYPE_1__ boot_cpu_data ; 

int mce_usable_address(struct mce *m)
{
	if (!(m->status & MCI_STATUS_ADDRV))
		return 0;

	/* Checks after this one are Intel-specific: */
	if (boot_cpu_data.x86_vendor != X86_VENDOR_INTEL)
		return 1;

	if (!(m->status & MCI_STATUS_MISCV))
		return 0;

	if (MCI_MISC_ADDR_LSB(m->misc) > PAGE_SHIFT)
		return 0;

	if (MCI_MISC_ADDR_MODE(m->misc) != MCI_MISC_ADDR_PHYS)
		return 0;

	return 1;
}