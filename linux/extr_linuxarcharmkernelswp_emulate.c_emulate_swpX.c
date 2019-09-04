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

/* Variables and functions */
 unsigned int EAGAIN ; 
 int EFAULT ; 
 unsigned int TYPE_SWPB ; 
 int /*<<< orphan*/  __user_swp_asm (unsigned int,unsigned int,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  __user_swpb_asm (unsigned int,unsigned int,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swpbcounter ; 
 int /*<<< orphan*/  swpcounter ; 
 int /*<<< orphan*/  uaccess_restore (unsigned int) ; 
 unsigned int uaccess_save_and_enable () ; 

__attribute__((used)) static int emulate_swpX(unsigned int address, unsigned int *data,
			unsigned int type)
{
	unsigned int res = 0;

	if ((type != TYPE_SWPB) && (address & 0x3)) {
		/* SWP to unaligned address not permitted */
		pr_debug("SWP instruction on unaligned pointer!\n");
		return -EFAULT;
	}

	while (1) {
		unsigned long temp;
		unsigned int __ua_flags;

		__ua_flags = uaccess_save_and_enable();
		if (type == TYPE_SWPB)
			__user_swpb_asm(*data, address, res, temp);
		else
			__user_swp_asm(*data, address, res, temp);
		uaccess_restore(__ua_flags);

		if (likely(res != -EAGAIN) || signal_pending(current))
			break;

		cond_resched();
	}

	if (res == 0) {
		if (type == TYPE_SWPB)
			swpbcounter++;
		else
			swpcounter++;
	}

	return res;
}