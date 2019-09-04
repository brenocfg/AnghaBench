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
typedef  int u64 ;

/* Variables and functions */
#define  KVM_REG_ARM_TIMER_CNT 130 
#define  KVM_REG_ARM_TIMER_CTL 129 
#define  KVM_REG_ARM_TIMER_CVAL 128 

__attribute__((used)) static bool is_timer_reg(u64 index)
{
	switch (index) {
	case KVM_REG_ARM_TIMER_CTL:
	case KVM_REG_ARM_TIMER_CNT:
	case KVM_REG_ARM_TIMER_CVAL:
		return true;
	}
	return false;
}