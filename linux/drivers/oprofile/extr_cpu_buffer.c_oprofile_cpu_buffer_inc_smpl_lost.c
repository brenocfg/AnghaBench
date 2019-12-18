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
struct oprofile_cpu_buffer {int /*<<< orphan*/  sample_lost_overflow; } ;

/* Variables and functions */
 int /*<<< orphan*/  op_cpu_buffer ; 
 struct oprofile_cpu_buffer* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void oprofile_cpu_buffer_inc_smpl_lost(void)
{
	struct oprofile_cpu_buffer *cpu_buf = this_cpu_ptr(&op_cpu_buffer);

	cpu_buf->sample_lost_overflow++;
}