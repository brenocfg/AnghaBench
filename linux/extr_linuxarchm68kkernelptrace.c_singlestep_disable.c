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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_SR ; 
 int /*<<< orphan*/  TIF_DELAYED_TRACE ; 
 unsigned long TRACE_BITS ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 unsigned long get_reg (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_reg (struct task_struct*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline void singlestep_disable(struct task_struct *child)
{
	unsigned long tmp = get_reg(child, PT_SR) & ~TRACE_BITS;
	put_reg(child, PT_SR, tmp);
	clear_tsk_thread_flag(child, TIF_DELAYED_TRACE);
}