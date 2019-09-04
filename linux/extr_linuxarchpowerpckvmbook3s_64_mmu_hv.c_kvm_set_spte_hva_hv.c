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
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  hva_handler_fn ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_handle_hva (struct kvm*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 int /*<<< orphan*/  kvm_unmap_radix ; 
 int /*<<< orphan*/  kvm_unmap_rmapp ; 

void kvm_set_spte_hva_hv(struct kvm *kvm, unsigned long hva, pte_t pte)
{
	hva_handler_fn handler;

	handler = kvm_is_radix(kvm) ? kvm_unmap_radix : kvm_unmap_rmapp;
	kvm_handle_hva(kvm, hva, handler);
}