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
typedef  int /*<<< orphan*/  u64 ;
struct sys_reg_desc {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMAIR_EL1 ; 
 int /*<<< orphan*/  amair_el1 ; 
 int /*<<< orphan*/  read_sysreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_write_sys_reg (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_amair_el1(struct kvm_vcpu *vcpu, const struct sys_reg_desc *r)
{
	u64 amair = read_sysreg(amair_el1);
	vcpu_write_sys_reg(vcpu, amair, AMAIR_EL1);
}