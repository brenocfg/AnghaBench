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
typedef  int /*<<< orphan*/  hva_handler_fn ;

/* Variables and functions */
 int kvm_handle_hva (struct kvm*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 int /*<<< orphan*/  kvm_test_age_radix ; 
 int /*<<< orphan*/  kvm_test_age_rmapp ; 

int kvm_test_age_hva_hv(struct kvm *kvm, unsigned long hva)
{
	hva_handler_fn handler;

	handler = kvm_is_radix(kvm) ? kvm_test_age_radix : kvm_test_age_rmapp;
	return kvm_handle_hva(kvm, hva, handler);
}