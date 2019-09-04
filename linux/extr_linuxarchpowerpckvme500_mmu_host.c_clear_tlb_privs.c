#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tlbe_ref {int dummy; } ;
struct kvmppc_vcpu_e500 {TYPE_2__** gtlb_priv; TYPE_1__* gtlb_params; } ;
struct TYPE_4__ {struct tlbe_ref ref; } ;
struct TYPE_3__ {int entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_e500_ref_release (struct tlbe_ref*) ; 

__attribute__((used)) static void clear_tlb_privs(struct kvmppc_vcpu_e500 *vcpu_e500)
{
	int tlbsel;
	int i;

	for (tlbsel = 0; tlbsel <= 1; tlbsel++) {
		for (i = 0; i < vcpu_e500->gtlb_params[tlbsel].entries; i++) {
			struct tlbe_ref *ref =
				&vcpu_e500->gtlb_priv[tlbsel][i].ref;
			kvmppc_e500_ref_release(ref);
		}
	}
}