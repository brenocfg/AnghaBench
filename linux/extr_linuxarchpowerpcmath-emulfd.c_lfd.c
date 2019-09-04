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
 scalar_t__ copy_from_user (void*,void*,int) ; 

int
lfd(void *frD, void *ea)
{
	if (copy_from_user(frD, ea, sizeof(double)))
		return -EFAULT;
#ifdef DEBUG
	printk("%s: D %p, ea %p: ", __func__, frD, ea);
	dump_double(frD);
	printk("\n");
#endif
	return 0;
}