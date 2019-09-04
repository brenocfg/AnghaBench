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
struct TYPE_2__ {int mmucfg; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  enum vcpu_ftr { ____Placeholder_vcpu_ftr } vcpu_ftr ;

/* Variables and functions */
 int MMUCFG_MAVN ; 
 int MMUCFG_MAVN_V2 ; 
#define  VCPU_FTR_MMU_V2 128 

__attribute__((used)) static inline bool has_feature(const struct kvm_vcpu *vcpu,
			       enum vcpu_ftr ftr)
{
	bool has_ftr;
	switch (ftr) {
	case VCPU_FTR_MMU_V2:
		has_ftr = ((vcpu->arch.mmucfg & MMUCFG_MAVN) == MMUCFG_MAVN_V2);
		break;
	default:
		return false;
	}
	return has_ftr;
}