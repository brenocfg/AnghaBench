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
struct genwqe_dev {int /*<<< orphan*/ * health_thread; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  genwqe_health_thread_running (struct genwqe_dev*) ; 
 int kthread_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int genwqe_health_check_stop(struct genwqe_dev *cd)
{
	int rc;

	if (!genwqe_health_thread_running(cd))
		return -EIO;

	rc = kthread_stop(cd->health_thread);
	cd->health_thread = NULL;
	return 0;
}