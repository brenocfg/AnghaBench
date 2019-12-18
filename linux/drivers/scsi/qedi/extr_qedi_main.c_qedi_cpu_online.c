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
struct qedi_percpu_s {struct task_struct* iothread; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  cpu_to_node (unsigned int) ; 
 int /*<<< orphan*/  kthread_bind (struct task_struct*,unsigned int) ; 
 struct task_struct* kthread_create_on_node (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  qedi_percpu ; 
 int /*<<< orphan*/  qedi_percpu_io_thread ; 
 struct qedi_percpu_s* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static int qedi_cpu_online(unsigned int cpu)
{
	struct qedi_percpu_s *p = this_cpu_ptr(&qedi_percpu);
	struct task_struct *thread;

	thread = kthread_create_on_node(qedi_percpu_io_thread, (void *)p,
					cpu_to_node(cpu),
					"qedi_thread/%d", cpu);
	if (IS_ERR(thread))
		return PTR_ERR(thread);

	kthread_bind(thread, cpu);
	p->iothread = thread;
	wake_up_process(thread);
	return 0;
}