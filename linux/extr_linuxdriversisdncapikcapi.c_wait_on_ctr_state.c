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
struct capi_ctr {unsigned int state; int /*<<< orphan*/  state_wait_queue; } ;

/* Variables and functions */
 unsigned int CAPI_CTR_DETACHED ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int ESRCH ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  capi_controller_lock ; 
 struct capi_ctr* capi_ctr_get (struct capi_ctr*) ; 
 int /*<<< orphan*/  capi_ctr_put (struct capi_ctr*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int wait_on_ctr_state(struct capi_ctr *ctr, unsigned int state)
{
	DEFINE_WAIT(wait);
	int retval = 0;

	ctr = capi_ctr_get(ctr);
	if (!ctr)
		return -ESRCH;

	for (;;) {
		prepare_to_wait(&ctr->state_wait_queue, &wait,
				TASK_INTERRUPTIBLE);

		if (ctr->state == state)
			break;
		if (ctr->state == CAPI_CTR_DETACHED) {
			retval = -ESRCH;
			break;
		}
		if (signal_pending(current)) {
			retval = -EINTR;
			break;
		}

		mutex_unlock(&capi_controller_lock);
		schedule();
		mutex_lock(&capi_controller_lock);
	}
	finish_wait(&ctr->state_wait_queue, &wait);

	capi_ctr_put(ctr);

	return retval;
}