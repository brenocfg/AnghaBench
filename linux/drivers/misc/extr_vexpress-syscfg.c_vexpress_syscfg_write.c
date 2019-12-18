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
struct vexpress_syscfg_func {int dummy; } ;

/* Variables and functions */
 int vexpress_syscfg_exec (struct vexpress_syscfg_func*,unsigned int,int,unsigned int*) ; 

__attribute__((used)) static int vexpress_syscfg_write(void *context, unsigned int index,
		unsigned int val)
{
	struct vexpress_syscfg_func *func = context;

	return vexpress_syscfg_exec(func, index, true, &val);
}