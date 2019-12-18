#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct task_struct {scalar_t__ mm; TYPE_1__* group_leader; } ;
struct TYPE_8__ {char* name; int /*<<< orphan*/  mode; } ;
struct kfd_process {TYPE_2__* lead_thread; TYPE_3__ attr_pasid; int /*<<< orphan*/  kobj; } ;
struct file {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {scalar_t__ pid; } ;
struct TYPE_6__ {scalar_t__ mm; } ;

/* Variables and functions */
 int EINVAL ; 
 struct kfd_process* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct kfd_process*) ; 
 int /*<<< orphan*/  KFD_SYSFS_FILE_MODE ; 
 struct kfd_process* create_process (struct task_struct*) ; 
 struct task_struct* current ; 
 struct kfd_process* find_process (struct task_struct*) ; 
 int /*<<< orphan*/  kfd_alloc_struct (int /*<<< orphan*/ ) ; 
 int kfd_process_init_cwsr_apu (struct kfd_process*,struct file*) ; 
 int /*<<< orphan*/  kfd_processes_mutex ; 
 int kobject_init_and_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 TYPE_5__ procfs ; 
 int /*<<< orphan*/  procfs_type ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_3__*) ; 
 int sysfs_create_file (int /*<<< orphan*/ ,TYPE_3__*) ; 

struct kfd_process *kfd_create_process(struct file *filep)
{
	struct kfd_process *process;
	struct task_struct *thread = current;
	int ret;

	if (!thread->mm)
		return ERR_PTR(-EINVAL);

	/* Only the pthreads threading model is supported. */
	if (thread->group_leader->mm != thread->mm)
		return ERR_PTR(-EINVAL);

	/*
	 * take kfd processes mutex before starting of process creation
	 * so there won't be a case where two threads of the same process
	 * create two kfd_process structures
	 */
	mutex_lock(&kfd_processes_mutex);

	/* A prior open of /dev/kfd could have already created the process. */
	process = find_process(thread);
	if (process) {
		pr_debug("Process already found\n");
	} else {
		process = create_process(thread);
		if (IS_ERR(process))
			goto out;

		ret = kfd_process_init_cwsr_apu(process, filep);
		if (ret) {
			process = ERR_PTR(ret);
			goto out;
		}

		if (!procfs.kobj)
			goto out;

		process->kobj = kfd_alloc_struct(process->kobj);
		if (!process->kobj) {
			pr_warn("Creating procfs kobject failed");
			goto out;
		}
		ret = kobject_init_and_add(process->kobj, &procfs_type,
					   procfs.kobj, "%d",
					   (int)process->lead_thread->pid);
		if (ret) {
			pr_warn("Creating procfs pid directory failed");
			goto out;
		}

		process->attr_pasid.name = "pasid";
		process->attr_pasid.mode = KFD_SYSFS_FILE_MODE;
		sysfs_attr_init(&process->attr_pasid);
		ret = sysfs_create_file(process->kobj, &process->attr_pasid);
		if (ret)
			pr_warn("Creating pasid for pid %d failed",
					(int)process->lead_thread->pid);
	}
out:
	mutex_unlock(&kfd_processes_mutex);

	return process;
}