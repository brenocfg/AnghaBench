#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  instruction_sigp_unknown; int /*<<< orphan*/  instruction_sigp_cpu_reset; int /*<<< orphan*/  instruction_sigp_init_cpu_reset; int /*<<< orphan*/  instruction_sigp_restart; int /*<<< orphan*/  instruction_sigp_start; int /*<<< orphan*/  instruction_sigp_prefix; int /*<<< orphan*/  instruction_sigp_store_adtl_status; int /*<<< orphan*/  instruction_sigp_store_status; int /*<<< orphan*/  instruction_sigp_stop_store_status; int /*<<< orphan*/  instruction_sigp_stop; } ;
struct kvm_vcpu {TYPE_2__ stat; TYPE_1__* kvm; } ;
struct TYPE_6__ {int /*<<< orphan*/  user_sigp; } ;
struct TYPE_4__ {TYPE_3__ arch; } ;

/* Variables and functions */
#define  SIGP_COND_EMERGENCY_SIGNAL 141 
#define  SIGP_CPU_RESET 140 
#define  SIGP_EMERGENCY_SIGNAL 139 
#define  SIGP_EXTERNAL_CALL 138 
#define  SIGP_INITIAL_CPU_RESET 137 
#define  SIGP_RESTART 136 
#define  SIGP_SENSE 135 
#define  SIGP_SENSE_RUNNING 134 
#define  SIGP_SET_PREFIX 133 
#define  SIGP_START 132 
#define  SIGP_STOP 131 
#define  SIGP_STOP_AND_STORE_STATUS 130 
#define  SIGP_STORE_ADDITIONAL_STATUS 129 
#define  SIGP_STORE_STATUS_AT_ADDRESS 128 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_sigp_order_in_user_space(struct kvm_vcpu *vcpu, u8 order_code,
					   u16 cpu_addr)
{
	if (!vcpu->kvm->arch.user_sigp)
		return 0;

	switch (order_code) {
	case SIGP_SENSE:
	case SIGP_EXTERNAL_CALL:
	case SIGP_EMERGENCY_SIGNAL:
	case SIGP_COND_EMERGENCY_SIGNAL:
	case SIGP_SENSE_RUNNING:
		return 0;
	/* update counters as we're directly dropping to user space */
	case SIGP_STOP:
		vcpu->stat.instruction_sigp_stop++;
		break;
	case SIGP_STOP_AND_STORE_STATUS:
		vcpu->stat.instruction_sigp_stop_store_status++;
		break;
	case SIGP_STORE_STATUS_AT_ADDRESS:
		vcpu->stat.instruction_sigp_store_status++;
		break;
	case SIGP_STORE_ADDITIONAL_STATUS:
		vcpu->stat.instruction_sigp_store_adtl_status++;
		break;
	case SIGP_SET_PREFIX:
		vcpu->stat.instruction_sigp_prefix++;
		break;
	case SIGP_START:
		vcpu->stat.instruction_sigp_start++;
		break;
	case SIGP_RESTART:
		vcpu->stat.instruction_sigp_restart++;
		break;
	case SIGP_INITIAL_CPU_RESET:
		vcpu->stat.instruction_sigp_init_cpu_reset++;
		break;
	case SIGP_CPU_RESET:
		vcpu->stat.instruction_sigp_cpu_reset++;
		break;
	default:
		vcpu->stat.instruction_sigp_unknown++;
	}
	VCPU_EVENT(vcpu, 3, "SIGP: order %u for CPU %d handled in userspace",
		   order_code, cpu_addr);

	return 1;
}