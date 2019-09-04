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
struct TYPE_2__ {int /*<<< orphan*/  gdbell_exits; int /*<<< orphan*/  dbell_exits; int /*<<< orphan*/  signal_exits; int /*<<< orphan*/  itlb_virt_miss_exits; int /*<<< orphan*/  itlb_real_miss_exits; int /*<<< orphan*/  mmio_exits; int /*<<< orphan*/  dtlb_virt_miss_exits; int /*<<< orphan*/  dtlb_real_miss_exits; int /*<<< orphan*/  syscall_exits; int /*<<< orphan*/  isi_exits; int /*<<< orphan*/  dsi_exits; int /*<<< orphan*/  emulated_inst_exits; int /*<<< orphan*/  dec_exits; int /*<<< orphan*/  ext_intr_exits; } ;
struct kvm_vcpu {TYPE_1__ stat; } ;

/* Variables and functions */
#define  DBELL_EXITS 141 
#define  DEC_EXITS 140 
#define  DSI_EXITS 139 
#define  DTLB_REAL_MISS_EXITS 138 
#define  DTLB_VIRT_MISS_EXITS 137 
#define  EMULATED_INST_EXITS 136 
#define  EXT_INTR_EXITS 135 
#define  GDBELL_EXITS 134 
#define  ISI_EXITS 133 
#define  ITLB_REAL_MISS_EXITS 132 
#define  ITLB_VIRT_MISS_EXITS 131 
#define  MMIO_EXITS 130 
#define  SIGNAL_EXITS 129 
#define  SYSCALL_EXITS 128 

__attribute__((used)) static inline void kvmppc_account_exit_stat(struct kvm_vcpu *vcpu, int type)
{
	/* type has to be known at build time for optimization */

	/* The BUILD_BUG_ON below breaks in funny ways, commented out
	 * for now ... -BenH
	BUILD_BUG_ON(!__builtin_constant_p(type));
	*/
	switch (type) {
	case EXT_INTR_EXITS:
		vcpu->stat.ext_intr_exits++;
		break;
	case DEC_EXITS:
		vcpu->stat.dec_exits++;
		break;
	case EMULATED_INST_EXITS:
		vcpu->stat.emulated_inst_exits++;
		break;
	case DSI_EXITS:
		vcpu->stat.dsi_exits++;
		break;
	case ISI_EXITS:
		vcpu->stat.isi_exits++;
		break;
	case SYSCALL_EXITS:
		vcpu->stat.syscall_exits++;
		break;
	case DTLB_REAL_MISS_EXITS:
		vcpu->stat.dtlb_real_miss_exits++;
		break;
	case DTLB_VIRT_MISS_EXITS:
		vcpu->stat.dtlb_virt_miss_exits++;
		break;
	case MMIO_EXITS:
		vcpu->stat.mmio_exits++;
		break;
	case ITLB_REAL_MISS_EXITS:
		vcpu->stat.itlb_real_miss_exits++;
		break;
	case ITLB_VIRT_MISS_EXITS:
		vcpu->stat.itlb_virt_miss_exits++;
		break;
	case SIGNAL_EXITS:
		vcpu->stat.signal_exits++;
		break;
	case DBELL_EXITS:
		vcpu->stat.dbell_exits++;
		break;
	case GDBELL_EXITS:
		vcpu->stat.gdbell_exits++;
		break;
	}
}