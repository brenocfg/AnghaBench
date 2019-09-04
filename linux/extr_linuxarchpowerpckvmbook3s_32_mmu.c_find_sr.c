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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;
typedef  int gva_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_get_sr (struct kvm_vcpu*,int) ; 

__attribute__((used)) static u32 find_sr(struct kvm_vcpu *vcpu, gva_t eaddr)
{
	return kvmppc_get_sr(vcpu, (eaddr >> 28) & 0xf);
}