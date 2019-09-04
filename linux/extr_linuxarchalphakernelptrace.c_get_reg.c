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
struct TYPE_2__ {unsigned long ieee_state; } ;

/* Variables and functions */
 unsigned long IEEE_SW_MASK ; 
 unsigned long* get_reg_addr (struct task_struct*,unsigned long) ; 
 unsigned long swcr_update_status (unsigned long,unsigned long) ; 
 TYPE_1__* task_thread_info (struct task_struct*) ; 

__attribute__((used)) static unsigned long
get_reg(struct task_struct * task, unsigned long regno)
{
	/* Special hack for fpcr -- combine hardware and software bits.  */
	if (regno == 63) {
		unsigned long fpcr = *get_reg_addr(task, regno);
		unsigned long swcr
		  = task_thread_info(task)->ieee_state & IEEE_SW_MASK;
		swcr = swcr_update_status(swcr, fpcr);
		return fpcr | swcr;
	}
	return *get_reg_addr(task, regno);
}