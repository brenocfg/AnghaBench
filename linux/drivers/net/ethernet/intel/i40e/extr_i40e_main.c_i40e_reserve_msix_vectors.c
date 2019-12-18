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
struct i40e_pf {TYPE_1__* pdev; int /*<<< orphan*/  msix_entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_MIN_MSIX ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int pci_enable_msix_range (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i40e_reserve_msix_vectors(struct i40e_pf *pf, int vectors)
{
	vectors = pci_enable_msix_range(pf->pdev, pf->msix_entries,
					I40E_MIN_MSIX, vectors);
	if (vectors < 0) {
		dev_info(&pf->pdev->dev,
			 "MSI-X vector reservation failed: %d\n", vectors);
		vectors = 0;
	}

	return vectors;
}