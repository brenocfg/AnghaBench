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
struct amdgpu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int amdgpu_vm_block_size ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void amdgpu_device_check_block_size(struct amdgpu_device *adev)
{
	/* defines number of bits in page table versus page directory,
	 * a page is 4KB so we have 12 bits offset, minimum 9 bits in the
	 * page table and the remaining bits are in the page directory */
	if (amdgpu_vm_block_size == -1)
		return;

	if (amdgpu_vm_block_size < 9) {
		dev_warn(adev->dev, "VM page table size (%d) too small\n",
			 amdgpu_vm_block_size);
		amdgpu_vm_block_size = -1;
	}
}