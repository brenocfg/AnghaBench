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
struct radeon_device {int dummy; } ;

/* Variables and functions */

void r100_pci_gart_tlb_flush(struct radeon_device *rdev)
{
	/* TODO: can we do somethings here ? */
	/* It seems hw only cache one entry so we should discard this
	 * entry otherwise if first GPU GART read hit this entry it
	 * could end up in wrong address. */
}