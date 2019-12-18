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
typedef  scalar_t__ u32 ;
struct radeon_device {scalar_t__ rio_mem_size; scalar_t__ rio_mem; } ;

/* Variables and functions */
 scalar_t__ RADEON_MM_DATA ; 
 scalar_t__ RADEON_MM_INDEX ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 

u32 r100_io_rreg(struct radeon_device *rdev, u32 reg)
{
	if (reg < rdev->rio_mem_size)
		return ioread32(rdev->rio_mem + reg);
	else {
		iowrite32(reg, rdev->rio_mem + RADEON_MM_INDEX);
		return ioread32(rdev->rio_mem + RADEON_MM_DATA);
	}
}