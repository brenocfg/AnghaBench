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
struct pci_dev {TYPE_1__* resource; } ;
struct TYPE_2__ {scalar_t__ start; int /*<<< orphan*/  end; } ;

/* Variables and functions */

__attribute__((used)) static void pci_fixup_unassign(struct pci_dev *dev)
{
	dev->resource[0].end -= dev->resource[0].start;
	dev->resource[0].start = 0;
}