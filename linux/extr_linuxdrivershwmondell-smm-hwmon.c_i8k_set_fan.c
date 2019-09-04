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
struct smm_regs {int ebx; int /*<<< orphan*/  eax; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I8K_SMM_SET_FAN ; 
 scalar_t__ disallow_fan_support ; 
 int i8k_fan_max ; 
 int i8k_get_fan_status (int) ; 
 scalar_t__ i8k_smm (struct smm_regs*) ; 

__attribute__((used)) static int i8k_set_fan(int fan, int speed)
{
	struct smm_regs regs = { .eax = I8K_SMM_SET_FAN, };

	if (disallow_fan_support)
		return -EINVAL;

	speed = (speed < 0) ? 0 : ((speed > i8k_fan_max) ? i8k_fan_max : speed);
	regs.ebx = (fan & 0xff) | (speed << 8);

	return i8k_smm(&regs) ? : i8k_get_fan_status(fan);
}