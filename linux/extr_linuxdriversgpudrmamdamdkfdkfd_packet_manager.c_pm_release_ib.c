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
struct packet_manager {int allocated; int /*<<< orphan*/  lock; int /*<<< orphan*/  ib_buffer_obj; TYPE_1__* dqm; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfd_gtt_sa_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void pm_release_ib(struct packet_manager *pm)
{
	mutex_lock(&pm->lock);
	if (pm->allocated) {
		kfd_gtt_sa_free(pm->dqm->dev, pm->ib_buffer_obj);
		pm->allocated = false;
	}
	mutex_unlock(&pm->lock);
}