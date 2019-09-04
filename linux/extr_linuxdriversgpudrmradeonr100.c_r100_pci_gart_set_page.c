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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * ptr; } ;
struct radeon_device {TYPE_1__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 

void r100_pci_gart_set_page(struct radeon_device *rdev, unsigned i,
			    uint64_t entry)
{
	u32 *gtt = rdev->gart.ptr;
	gtt[i] = cpu_to_le32(lower_32_bits(entry));
}