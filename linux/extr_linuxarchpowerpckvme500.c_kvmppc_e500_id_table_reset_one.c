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
struct vcpu_id_table {TYPE_1__*** id; } ;
struct kvmppc_vcpu_e500 {struct vcpu_id_table* idt; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pentry; scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NUM_TIDS ; 
 int /*<<< orphan*/  kvmppc_e500_recalc_shadow_pid (struct kvmppc_vcpu_e500*) ; 

__attribute__((used)) static inline void kvmppc_e500_id_table_reset_one(
			       struct kvmppc_vcpu_e500 *vcpu_e500,
			       int as, int pid, int pr)
{
	struct vcpu_id_table *idt = vcpu_e500->idt;

	BUG_ON(as >= 2);
	BUG_ON(pid >= NUM_TIDS);
	BUG_ON(pr >= 2);

	idt->id[as][pid][pr].val = 0;
	idt->id[as][pid][pr].pentry = NULL;

	/* Update shadow pid when mappings are changed */
	kvmppc_e500_recalc_shadow_pid(vcpu_e500);
}