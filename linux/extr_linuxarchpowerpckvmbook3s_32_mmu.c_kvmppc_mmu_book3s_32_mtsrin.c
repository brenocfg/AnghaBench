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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int SID_SHIFT ; 
 int /*<<< orphan*/  kvmppc_mmu_map_segment (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_set_sr (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_mmu_book3s_32_mtsrin(struct kvm_vcpu *vcpu, u32 srnum,
					ulong value)
{
	kvmppc_set_sr(vcpu, srnum, value);
	kvmppc_mmu_map_segment(vcpu, srnum << SID_SHIFT);
}