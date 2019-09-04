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
struct x86_emulate_ctxt {int dummy; } ;
struct desc_ptr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_idt ) (int /*<<< orphan*/ ,struct desc_ptr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct desc_ptr*) ; 

__attribute__((used)) static void emulator_get_idt(struct x86_emulate_ctxt *ctxt, struct desc_ptr *dt)
{
	kvm_x86_ops->get_idt(emul_to_vcpu(ctxt), dt);
}