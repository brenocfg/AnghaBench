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
struct resource {int end; int start; int /*<<< orphan*/  flags; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_UNSET ; 

__attribute__((used)) static void quirk_intel_th_dnv(struct pci_dev *dev)
{
	struct resource *r = &dev->resource[4];

	/*
	 * Denverton reports 2k of RTIT_BAR (intel_th resource 4), which
	 * appears to be 4 MB in reality.
	 */
	if (r->end == r->start + 0x7ff) {
		r->start = 0;
		r->end   = 0x3fffff;
		r->flags |= IORESOURCE_UNSET;
	}
}