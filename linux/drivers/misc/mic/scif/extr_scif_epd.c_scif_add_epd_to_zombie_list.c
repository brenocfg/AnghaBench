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
struct scif_endpt {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  misc_work; int /*<<< orphan*/  eplock; int /*<<< orphan*/  nr_zombies; int /*<<< orphan*/  zombie; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIFEP_ZOMBIE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 TYPE_1__ scif_info ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void scif_add_epd_to_zombie_list(struct scif_endpt *ep, bool eplock_held)
{
	if (!eplock_held)
		mutex_lock(&scif_info.eplock);
	spin_lock(&ep->lock);
	ep->state = SCIFEP_ZOMBIE;
	spin_unlock(&ep->lock);
	list_add_tail(&ep->list, &scif_info.zombie);
	scif_info.nr_zombies++;
	if (!eplock_held)
		mutex_unlock(&scif_info.eplock);
	schedule_work(&scif_info.misc_work);
}