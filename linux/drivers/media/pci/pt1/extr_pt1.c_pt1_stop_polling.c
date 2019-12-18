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
struct pt1 {int /*<<< orphan*/  lock; int /*<<< orphan*/ * kthread; TYPE_1__** adaps; } ;
struct TYPE_2__ {scalar_t__ users; } ;

/* Variables and functions */
 int PT1_NR_ADAPS ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pt1_stop_polling(struct pt1 *pt1)
{
	int i, count;

	mutex_lock(&pt1->lock);
	for (i = 0, count = 0; i < PT1_NR_ADAPS; i++)
		count += pt1->adaps[i]->users;

	if (count == 0 && pt1->kthread) {
		kthread_stop(pt1->kthread);
		pt1->kthread = NULL;
	}
	mutex_unlock(&pt1->lock);
}