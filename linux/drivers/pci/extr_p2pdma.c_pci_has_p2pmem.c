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
struct pci_dev {TYPE_1__* p2pdma; } ;
struct TYPE_2__ {scalar_t__ p2pmem_published; } ;

/* Variables and functions */

bool pci_has_p2pmem(struct pci_dev *pdev)
{
	return pdev->p2pdma && pdev->p2pdma->p2pmem_published;
}