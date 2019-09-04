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
struct TYPE_2__ {scalar_t__ buf_size; } ;
typedef  TYPE_1__ pfm_default_smpl_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int EINVAL ; 
 scalar_t__ PFM_DEFAULT_SMPL_MIN_BUF_SIZE ; 
 int /*<<< orphan*/  task_pid_nr (struct task_struct*) ; 

__attribute__((used)) static int
default_validate(struct task_struct *task, unsigned int flags, int cpu, void *data)
{
	pfm_default_smpl_arg_t *arg = (pfm_default_smpl_arg_t*)data;
	int ret = 0;

	if (data == NULL) {
		DPRINT(("[%d] no argument passed\n", task_pid_nr(task)));
		return -EINVAL;
	}

	DPRINT(("[%d] validate flags=0x%x CPU%d\n", task_pid_nr(task), flags, cpu));

	/*
	 * must hold at least the buffer header + one minimally sized entry
	 */
	if (arg->buf_size < PFM_DEFAULT_SMPL_MIN_BUF_SIZE) return -EINVAL;

	DPRINT(("buf_size=%lu\n", arg->buf_size));

	return ret;
}