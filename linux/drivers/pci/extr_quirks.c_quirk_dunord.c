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
struct resource {int end; scalar_t__ start; int /*<<< orphan*/  flags; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_UNSET ; 

__attribute__((used)) static void quirk_dunord(struct pci_dev *dev)
{
	struct resource *r = &dev->resource[1];

	r->flags |= IORESOURCE_UNSET;
	r->start = 0;
	r->end = 0xffffff;
}