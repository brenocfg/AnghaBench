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
typedef  scalar_t__ sync_buffer_state ;
struct task_struct {int dummy; } ;
struct op_sample {unsigned long event; int /*<<< orphan*/  eip; } ;
struct op_entry {int dummy; } ;
struct mm_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bt_lost_no_mapping; } ;

/* Variables and functions */
 unsigned long IS_KERNEL ; 
 unsigned long KERNEL_CTX_SWITCH ; 
 unsigned long TRACE_BEGIN ; 
 unsigned long USER_CTX_SWITCH ; 
 int /*<<< orphan*/  add_cpu_switch (int) ; 
 int /*<<< orphan*/  add_data (struct op_entry*,struct mm_struct*) ; 
 int /*<<< orphan*/  add_kernel_ctx_switch (unsigned long) ; 
 scalar_t__ add_sample (struct mm_struct*,struct op_sample*,int) ; 
 int /*<<< orphan*/  add_trace_begin () ; 
 int /*<<< orphan*/  add_user_ctx_switch (struct task_struct*,unsigned long) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_mutex ; 
 unsigned long get_exec_dcookie (struct mm_struct*) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 scalar_t__ is_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_done (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long op_cpu_buffer_entries (int) ; 
 scalar_t__ op_cpu_buffer_get_data (struct op_entry*,unsigned long*) ; 
 scalar_t__ op_cpu_buffer_get_size (struct op_entry*) ; 
 struct op_sample* op_cpu_buffer_read_entry (struct op_entry*,int) ; 
 int /*<<< orphan*/  op_cpu_buffer_reset (int) ; 
 TYPE_1__ oprofile_stats ; 
 int /*<<< orphan*/  release_mm (struct mm_struct*) ; 
 scalar_t__ sb_bt_ignore ; 
 scalar_t__ sb_bt_start ; 
 scalar_t__ sb_buffer_start ; 
 scalar_t__ sb_sample_start ; 

void sync_buffer(int cpu)
{
	struct mm_struct *mm = NULL;
	struct mm_struct *oldmm;
	unsigned long val;
	struct task_struct *new;
	unsigned long cookie = 0;
	int in_kernel = 1;
	sync_buffer_state state = sb_buffer_start;
	unsigned int i;
	unsigned long available;
	unsigned long flags;
	struct op_entry entry;
	struct op_sample *sample;

	mutex_lock(&buffer_mutex);

	add_cpu_switch(cpu);

	op_cpu_buffer_reset(cpu);
	available = op_cpu_buffer_entries(cpu);

	for (i = 0; i < available; ++i) {
		sample = op_cpu_buffer_read_entry(&entry, cpu);
		if (!sample)
			break;

		if (is_code(sample->eip)) {
			flags = sample->event;
			if (flags & TRACE_BEGIN) {
				state = sb_bt_start;
				add_trace_begin();
			}
			if (flags & KERNEL_CTX_SWITCH) {
				/* kernel/userspace switch */
				in_kernel = flags & IS_KERNEL;
				if (state == sb_buffer_start)
					state = sb_sample_start;
				add_kernel_ctx_switch(flags & IS_KERNEL);
			}
			if (flags & USER_CTX_SWITCH
			    && op_cpu_buffer_get_data(&entry, &val)) {
				/* userspace context switch */
				new = (struct task_struct *)val;
				oldmm = mm;
				release_mm(oldmm);
				mm = get_task_mm(new);
				if (mm != oldmm)
					cookie = get_exec_dcookie(mm);
				add_user_ctx_switch(new, cookie);
			}
			if (op_cpu_buffer_get_size(&entry))
				add_data(&entry, mm);
			continue;
		}

		if (state < sb_bt_start)
			/* ignore sample */
			continue;

		if (add_sample(mm, sample, in_kernel))
			continue;

		/* ignore backtraces if failed to add a sample */
		if (state == sb_bt_start) {
			state = sb_bt_ignore;
			atomic_inc(&oprofile_stats.bt_lost_no_mapping);
		}
	}
	release_mm(mm);

	mark_done(cpu);

	mutex_unlock(&buffer_mutex);
}