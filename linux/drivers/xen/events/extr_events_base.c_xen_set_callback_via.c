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
struct xen_hvm_param {int /*<<< orphan*/  value; int /*<<< orphan*/  index; int /*<<< orphan*/  domid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 int /*<<< orphan*/  HVMOP_set_param ; 
 int /*<<< orphan*/  HVM_PARAM_CALLBACK_IRQ ; 
 int HYPERVISOR_hvm_op (int /*<<< orphan*/ ,struct xen_hvm_param*) ; 

int xen_set_callback_via(uint64_t via)
{
	struct xen_hvm_param a;
	a.domid = DOMID_SELF;
	a.index = HVM_PARAM_CALLBACK_IRQ;
	a.value = via;
	return HYPERVISOR_hvm_op(HVMOP_set_param, &a);
}