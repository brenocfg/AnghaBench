#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* shadow_pid1; void* shadow_pid; } ;
struct TYPE_6__ {TYPE_1__ arch; } ;
struct kvmppc_vcpu_e500 {TYPE_2__ vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cur_as (TYPE_2__*) ; 
 int /*<<< orphan*/  get_cur_pid (TYPE_2__*) ; 
 int /*<<< orphan*/  get_cur_pr (TYPE_2__*) ; 
 void* kvmppc_e500_get_sid (struct kvmppc_vcpu_e500*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static void kvmppc_e500_recalc_shadow_pid(struct kvmppc_vcpu_e500 *vcpu_e500)
{
	preempt_disable();
	vcpu_e500->vcpu.arch.shadow_pid = kvmppc_e500_get_sid(vcpu_e500,
			get_cur_as(&vcpu_e500->vcpu),
			get_cur_pid(&vcpu_e500->vcpu),
			get_cur_pr(&vcpu_e500->vcpu), 1);
	vcpu_e500->vcpu.arch.shadow_pid1 = kvmppc_e500_get_sid(vcpu_e500,
			get_cur_as(&vcpu_e500->vcpu), 0,
			get_cur_pr(&vcpu_e500->vcpu), 1);
	preempt_enable();
}