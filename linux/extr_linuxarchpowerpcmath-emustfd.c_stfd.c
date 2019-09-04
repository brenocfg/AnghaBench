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
 int EFAULT ; 
 scalar_t__ copy_to_user (void*,void*,int) ; 

int
stfd(void *frS, void *ea)
{
#if 0
#ifdef DEBUG
	printk("%s: S %p, ea %p: ", __func__, frS, ea);
	dump_double(frS);
	printk("\n");
#endif
#endif

	if (copy_to_user(ea, frS, sizeof(double)))
		return -EFAULT;

	return 0;
}