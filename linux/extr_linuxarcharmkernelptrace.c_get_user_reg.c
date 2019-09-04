#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_2__ {long* uregs; } ;

/* Variables and functions */
 TYPE_1__* task_pt_regs (struct task_struct*) ; 

__attribute__((used)) static inline long get_user_reg(struct task_struct *task, int offset)
{
	return task_pt_regs(task)->uregs[offset];
}