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
struct TYPE_2__ {int table_size; int num_gpu_pages; scalar_t__ robj; } ;
struct radeon_device {TYPE_1__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int radeon_gart_init (struct radeon_device*) ; 
 int radeon_gart_table_vram_alloc (struct radeon_device*) ; 

int r600_pcie_gart_init(struct radeon_device *rdev)
{
	int r;

	if (rdev->gart.robj) {
		WARN(1, "R600 PCIE GART already initialized\n");
		return 0;
	}
	/* Initialize common gart structure */
	r = radeon_gart_init(rdev);
	if (r)
		return r;
	rdev->gart.table_size = rdev->gart.num_gpu_pages * 8;
	return radeon_gart_table_vram_alloc(rdev);
}