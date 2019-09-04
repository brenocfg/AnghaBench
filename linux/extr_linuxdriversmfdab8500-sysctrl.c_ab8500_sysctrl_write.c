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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/ * sysctrl_dev ; 
 int /*<<< orphan*/  valid_bank (int) ; 

int ab8500_sysctrl_write(u16 reg, u8 mask, u8 value)
{
	u8 bank;

	if (sysctrl_dev == NULL)
		return -EPROBE_DEFER;

	bank = (reg >> 8);
	if (!valid_bank(bank)) {
		pr_err("invalid bank\n");
		return -EINVAL;
	}

	return abx500_mask_and_set_register_interruptible(sysctrl_dev, bank,
		(u8)(reg & 0xFF), mask, value);
}