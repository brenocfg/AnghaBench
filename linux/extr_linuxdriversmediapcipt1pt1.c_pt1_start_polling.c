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
struct pt1 {int /*<<< orphan*/  lock; int /*<<< orphan*/ * kthread; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct pt1*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt1_thread ; 

__attribute__((used)) static int pt1_start_polling(struct pt1 *pt1)
{
	int ret = 0;

	mutex_lock(&pt1->lock);
	if (!pt1->kthread) {
		pt1->kthread = kthread_run(pt1_thread, pt1, "earth-pt1");
		if (IS_ERR(pt1->kthread)) {
			ret = PTR_ERR(pt1->kthread);
			pt1->kthread = NULL;
		}
	}
	mutex_unlock(&pt1->lock);
	return ret;
}