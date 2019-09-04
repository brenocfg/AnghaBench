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

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  do_kvm_unmap_hva (struct kvm*,unsigned long,scalar_t__) ; 

__attribute__((used)) static void kvm_set_spte_hva_pr(struct kvm *kvm, unsigned long hva, pte_t pte)
{
	/* The page will get remapped properly on its next fault */
	do_kvm_unmap_hva(kvm, hva, hva + PAGE_SIZE);
}