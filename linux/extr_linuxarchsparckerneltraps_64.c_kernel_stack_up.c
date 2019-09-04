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
struct reg_window {unsigned long* ins; } ;

/* Variables and functions */
 scalar_t__ STACK_BIAS ; 

__attribute__((used)) static inline struct reg_window *kernel_stack_up(struct reg_window *rw)
{
	unsigned long fp = rw->ins[6];

	if (!fp)
		return NULL;

	return (struct reg_window *) (fp + STACK_BIAS);
}