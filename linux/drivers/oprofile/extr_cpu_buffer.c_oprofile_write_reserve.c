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
struct pt_regs {int dummy; } ;
struct oprofile_cpu_buffer {int /*<<< orphan*/  sample_lost_overflow; int /*<<< orphan*/  sample_received; } ;
struct op_sample {scalar_t__ event; int /*<<< orphan*/  eip; } ;
struct op_entry {int /*<<< orphan*/ * event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESCAPE_CODE ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ op_add_code (struct oprofile_cpu_buffer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_cpu_buffer ; 
 int /*<<< orphan*/  op_cpu_buffer_add_data (struct op_entry*,unsigned long) ; 
 struct op_sample* op_cpu_buffer_write_reserve (struct op_entry*,int) ; 
 struct oprofile_cpu_buffer* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs* const) ; 

void
oprofile_write_reserve(struct op_entry *entry, struct pt_regs * const regs,
		       unsigned long pc, int code, int size)
{
	struct op_sample *sample;
	int is_kernel = !user_mode(regs);
	struct oprofile_cpu_buffer *cpu_buf = this_cpu_ptr(&op_cpu_buffer);

	cpu_buf->sample_received++;

	/* no backtraces for samples with data */
	if (op_add_code(cpu_buf, 0, is_kernel, current))
		goto fail;

	sample = op_cpu_buffer_write_reserve(entry, size + 2);
	if (!sample)
		goto fail;
	sample->eip = ESCAPE_CODE;
	sample->event = 0;		/* no flags */

	op_cpu_buffer_add_data(entry, code);
	op_cpu_buffer_add_data(entry, pc);

	return;

fail:
	entry->event = NULL;
	cpu_buf->sample_lost_overflow++;
}