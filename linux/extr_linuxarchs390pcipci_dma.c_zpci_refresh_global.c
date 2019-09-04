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
typedef  int u64 ;
struct zpci_dev {int iommu_pages; int /*<<< orphan*/  start_dma; scalar_t__ fh; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int zpci_refresh_trans (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zpci_refresh_global(struct zpci_dev *zdev)
{
	return zpci_refresh_trans((u64) zdev->fh << 32, zdev->start_dma,
				  zdev->iommu_pages * PAGE_SIZE);
}