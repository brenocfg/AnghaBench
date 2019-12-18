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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PTE_EXECUTABLE ; 
 int /*<<< orphan*/  AMDGPU_PTE_MTYPE_NV10 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDGPU_PTE_PRT ; 
 int /*<<< orphan*/  AMDGPU_PTE_READABLE ; 
 int /*<<< orphan*/  AMDGPU_PTE_WRITEABLE ; 
#define  AMDGPU_VM_MTYPE_CC 132 
#define  AMDGPU_VM_MTYPE_DEFAULT 131 
 int AMDGPU_VM_MTYPE_MASK ; 
#define  AMDGPU_VM_MTYPE_NC 130 
#define  AMDGPU_VM_MTYPE_UC 129 
#define  AMDGPU_VM_MTYPE_WC 128 
 int AMDGPU_VM_PAGE_EXECUTABLE ; 
 int AMDGPU_VM_PAGE_PRT ; 
 int AMDGPU_VM_PAGE_READABLE ; 
 int AMDGPU_VM_PAGE_WRITEABLE ; 
 int /*<<< orphan*/  MTYPE_CC ; 
 int /*<<< orphan*/  MTYPE_NC ; 
 int /*<<< orphan*/  MTYPE_UC ; 
 int /*<<< orphan*/  MTYPE_WC ; 

__attribute__((used)) static uint64_t gmc_v10_0_get_vm_pte_flags(struct amdgpu_device *adev,
					   uint32_t flags)
{
	uint64_t pte_flag = 0;

	if (flags & AMDGPU_VM_PAGE_EXECUTABLE)
		pte_flag |= AMDGPU_PTE_EXECUTABLE;
	if (flags & AMDGPU_VM_PAGE_READABLE)
		pte_flag |= AMDGPU_PTE_READABLE;
	if (flags & AMDGPU_VM_PAGE_WRITEABLE)
		pte_flag |= AMDGPU_PTE_WRITEABLE;

	switch (flags & AMDGPU_VM_MTYPE_MASK) {
	case AMDGPU_VM_MTYPE_DEFAULT:
		pte_flag |= AMDGPU_PTE_MTYPE_NV10(MTYPE_NC);
		break;
	case AMDGPU_VM_MTYPE_NC:
		pte_flag |= AMDGPU_PTE_MTYPE_NV10(MTYPE_NC);
		break;
	case AMDGPU_VM_MTYPE_WC:
		pte_flag |= AMDGPU_PTE_MTYPE_NV10(MTYPE_WC);
		break;
	case AMDGPU_VM_MTYPE_CC:
		pte_flag |= AMDGPU_PTE_MTYPE_NV10(MTYPE_CC);
		break;
	case AMDGPU_VM_MTYPE_UC:
		pte_flag |= AMDGPU_PTE_MTYPE_NV10(MTYPE_UC);
		break;
	default:
		pte_flag |= AMDGPU_PTE_MTYPE_NV10(MTYPE_NC);
		break;
	}

	if (flags & AMDGPU_VM_PAGE_PRT)
		pte_flag |= AMDGPU_PTE_PRT;

	return pte_flag;
}