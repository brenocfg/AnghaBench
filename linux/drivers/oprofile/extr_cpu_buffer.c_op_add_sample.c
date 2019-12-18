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
struct op_sample {unsigned long eip; unsigned long event; } ;
struct op_entry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int op_cpu_buffer_write_commit (struct op_entry*) ; 
 struct op_sample* op_cpu_buffer_write_reserve (struct op_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
op_add_sample(struct oprofile_cpu_buffer *cpu_buf,
	      unsigned long pc, unsigned long event)
{
	struct op_entry entry;
	struct op_sample *sample;

	sample = op_cpu_buffer_write_reserve(&entry, 0);
	if (!sample)
		return -ENOMEM;

	sample->eip = pc;
	sample->event = event;

	return op_cpu_buffer_write_commit(&entry);
}