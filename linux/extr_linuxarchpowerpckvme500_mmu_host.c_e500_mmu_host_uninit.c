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
struct kvmppc_vcpu_e500 {int /*<<< orphan*/  h2g_tlb1_rmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void e500_mmu_host_uninit(struct kvmppc_vcpu_e500 *vcpu_e500)
{
	kfree(vcpu_e500->h2g_tlb1_rmap);
}