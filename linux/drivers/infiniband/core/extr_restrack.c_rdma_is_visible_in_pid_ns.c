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
struct rdma_restrack_entry {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_pid_ns ; 
 scalar_t__ rdma_is_kernel_res (struct rdma_restrack_entry*) ; 
 int /*<<< orphan*/ * task_active_pid_ns (int /*<<< orphan*/ ) ; 
 int task_pid_vnr (int /*<<< orphan*/ ) ; 

bool rdma_is_visible_in_pid_ns(struct rdma_restrack_entry *res)
{
	/*
	 * 1. Kern resources should be visible in init
	 *    namespace only
	 * 2. Present only resources visible in the current
	 *     namespace
	 */
	if (rdma_is_kernel_res(res))
		return task_active_pid_ns(current) == &init_pid_ns;

	/* PID 0 means that resource is not found in current namespace */
	return task_pid_vnr(res->task);
}