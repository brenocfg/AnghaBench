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
struct user_regset {int dummy; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int NUM_DSP_REGS ; 
 scalar_t__ cpu_has_dsp ; 

__attribute__((used)) static int dsp_active(struct task_struct *target,
		      const struct user_regset *regset)
{
	return cpu_has_dsp ? NUM_DSP_REGS + 1 : -ENODEV;
}