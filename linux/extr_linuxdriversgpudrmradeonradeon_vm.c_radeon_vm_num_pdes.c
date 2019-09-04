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
struct TYPE_2__ {int max_pfn; } ;
struct radeon_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int radeon_vm_block_size ; 

__attribute__((used)) static unsigned radeon_vm_num_pdes(struct radeon_device *rdev)
{
	return rdev->vm_manager.max_pfn >> radeon_vm_block_size;
}