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
struct skd_device {scalar_t__ cq_dma_address; int /*<<< orphan*/ * skcomp_table; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKD_SKCOMP_SIZE ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void skd_free_skcomp(struct skd_device *skdev)
{
	if (skdev->skcomp_table)
		pci_free_consistent(skdev->pdev, SKD_SKCOMP_SIZE,
				    skdev->skcomp_table, skdev->cq_dma_address);

	skdev->skcomp_table = NULL;
	skdev->cq_dma_address = 0;
}