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
struct smm_regs {int eax; int ebx; } ;

/* Variables and functions */
 int EINVAL ; 
 int I8K_SMM_GET_SPEED ; 
 scalar_t__ disallow_fan_support ; 
 int i8k_fan_mult ; 
 scalar_t__ i8k_smm (struct smm_regs*) ; 

__attribute__((used)) static int i8k_get_fan_speed(int fan)
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_SPEED, };

	if (disallow_fan_support)
		return -EINVAL;

	regs.ebx = fan & 0xff;
	return i8k_smm(&regs) ? : (regs.eax & 0xffff) * i8k_fan_mult;
}