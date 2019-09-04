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
struct kfd_process {int /*<<< orphan*/  mutex; int /*<<< orphan*/  pqm; int /*<<< orphan*/  pasid; } ;
struct kfd_ioctl_destroy_queue_args {int /*<<< orphan*/  queue_id; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pqm_destroy_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kfd_ioctl_destroy_queue(struct file *filp, struct kfd_process *p,
					void *data)
{
	int retval;
	struct kfd_ioctl_destroy_queue_args *args = data;

	pr_debug("Destroying queue id %d for pasid %d\n",
				args->queue_id,
				p->pasid);

	mutex_lock(&p->mutex);

	retval = pqm_destroy_queue(&p->pqm, args->queue_id);

	mutex_unlock(&p->mutex);
	return retval;
}