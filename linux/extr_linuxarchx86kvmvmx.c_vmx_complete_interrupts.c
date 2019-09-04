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
struct vcpu_vmx {int /*<<< orphan*/  idt_vectoring_info; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDT_VECTORING_ERROR_CODE ; 
 int /*<<< orphan*/  VM_EXIT_INSTRUCTION_LEN ; 
 int /*<<< orphan*/  __vmx_complete_interrupts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_complete_interrupts(struct vcpu_vmx *vmx)
{
	__vmx_complete_interrupts(&vmx->vcpu, vmx->idt_vectoring_info,
				  VM_EXIT_INSTRUCTION_LEN,
				  IDT_VECTORING_ERROR_CODE);
}