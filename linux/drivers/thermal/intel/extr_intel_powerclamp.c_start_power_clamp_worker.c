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
struct powerclamp_worker_data {unsigned long cpu; int clamping; int /*<<< orphan*/  balancing_work; struct kthread_worker* worker; int /*<<< orphan*/  idle_injection_work; scalar_t__ count; } ;
struct kthread_worker {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct kthread_worker*) ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  clamp_balancing_func ; 
 int /*<<< orphan*/  clamp_idle_injection_func ; 
 int /*<<< orphan*/  cpu_clamping_mask ; 
 struct kthread_worker* kthread_create_worker_on_cpu (unsigned long,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  kthread_init_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_queue_work (struct kthread_worker*,int /*<<< orphan*/ *) ; 
 struct powerclamp_worker_data* per_cpu_ptr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparam ; 
 int /*<<< orphan*/  worker_data ; 

__attribute__((used)) static void start_power_clamp_worker(unsigned long cpu)
{
	struct powerclamp_worker_data *w_data = per_cpu_ptr(worker_data, cpu);
	struct kthread_worker *worker;

	worker = kthread_create_worker_on_cpu(cpu, 0, "kidle_inj/%ld", cpu);
	if (IS_ERR(worker))
		return;

	w_data->worker = worker;
	w_data->count = 0;
	w_data->cpu = cpu;
	w_data->clamping = true;
	set_bit(cpu, cpu_clamping_mask);
	sched_setscheduler(worker->task, SCHED_FIFO, &sparam);
	kthread_init_work(&w_data->balancing_work, clamp_balancing_func);
	kthread_init_delayed_work(&w_data->idle_injection_work,
				  clamp_idle_injection_func);
	kthread_queue_work(w_data->worker, &w_data->balancing_work);
}