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
struct kvmppc_vcpu_e500 {int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int MAS5_SGS ; 
 int /*<<< orphan*/  SPRN_MAS5 ; 
 int get_lpid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

void kvmppc_e500_tlbil_all(struct kvmppc_vcpu_e500 *vcpu_e500)
{
	unsigned long flags;

	local_irq_save(flags);
	mtspr(SPRN_MAS5, MAS5_SGS | get_lpid(&vcpu_e500->vcpu));
	asm volatile("tlbilxlpid");
	mtspr(SPRN_MAS5, 0);
	local_irq_restore(flags);
}