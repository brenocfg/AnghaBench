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
typedef  int /*<<< orphan*/  vm_fault_t ;
typedef  int u64 ;
struct vm_area_struct {int dummy; } ;
struct ocxl_context {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int ocxl_afu_irq_get_addr (struct ocxl_context*,int) ; 
 int ocxl_irq_offset_to_id (struct ocxl_context*,int) ; 
 int /*<<< orphan*/  vmf_insert_pfn (struct vm_area_struct*,unsigned long,int) ; 

__attribute__((used)) static vm_fault_t map_afu_irq(struct vm_area_struct *vma, unsigned long address,
		u64 offset, struct ocxl_context *ctx)
{
	u64 trigger_addr;
	int irq_id = ocxl_irq_offset_to_id(ctx, offset);

	trigger_addr = ocxl_afu_irq_get_addr(ctx, irq_id);
	if (!trigger_addr)
		return VM_FAULT_SIGBUS;

	return vmf_insert_pfn(vma, address, trigger_addr >> PAGE_SHIFT);
}