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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int RADEON_GPU_PAGE_ALIGN (int) ; 
 int radeon_vm_num_pdes (struct radeon_device*) ; 

__attribute__((used)) static unsigned radeon_vm_directory_size(struct radeon_device *rdev)
{
	return RADEON_GPU_PAGE_ALIGN(radeon_vm_num_pdes(rdev) * 8);
}