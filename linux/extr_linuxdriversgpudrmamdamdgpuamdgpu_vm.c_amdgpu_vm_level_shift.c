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
struct TYPE_2__ {int /*<<< orphan*/  block_size; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_1__ vm_manager; } ;

/* Variables and functions */
#define  AMDGPU_VM_PDB0 131 
#define  AMDGPU_VM_PDB1 130 
#define  AMDGPU_VM_PDB2 129 
#define  AMDGPU_VM_PTB 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static unsigned amdgpu_vm_level_shift(struct amdgpu_device *adev,
				      unsigned level)
{
	unsigned shift = 0xff;

	switch (level) {
	case AMDGPU_VM_PDB2:
	case AMDGPU_VM_PDB1:
	case AMDGPU_VM_PDB0:
		shift = 9 * (AMDGPU_VM_PDB0 - level) +
			adev->vm_manager.block_size;
		break;
	case AMDGPU_VM_PTB:
		shift = 0;
		break;
	default:
		dev_err(adev->dev, "the level%d isn't supported.\n", level);
	}

	return shift;
}