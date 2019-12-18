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
struct oprofile_cpu_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_sample (struct oprofile_cpu_buffer*,unsigned long,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_cpu_buffer ; 
 struct oprofile_cpu_buffer* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void oprofile_add_pc(unsigned long pc, int is_kernel, unsigned long event)
{
	struct oprofile_cpu_buffer *cpu_buf = this_cpu_ptr(&op_cpu_buffer);
	log_sample(cpu_buf, pc, 0, is_kernel, event, NULL);
}