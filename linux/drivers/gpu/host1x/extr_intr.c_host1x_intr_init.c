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
typedef  unsigned int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  thresh_irq_name; int /*<<< orphan*/  wait_head; int /*<<< orphan*/  lock; } ;
struct host1x_syncpt {TYPE_1__ intr; } ;
struct host1x {unsigned int intr_syncpt_irq; struct host1x_syncpt* syncpt; int /*<<< orphan*/  intr_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host1x_intr_start (struct host1x*) ; 
 unsigned int host1x_syncpt_nb_pts (struct host1x*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int host1x_intr_init(struct host1x *host, unsigned int irq_sync)
{
	unsigned int id;
	u32 nb_pts = host1x_syncpt_nb_pts(host);

	mutex_init(&host->intr_mutex);
	host->intr_syncpt_irq = irq_sync;

	for (id = 0; id < nb_pts; ++id) {
		struct host1x_syncpt *syncpt = host->syncpt + id;

		spin_lock_init(&syncpt->intr.lock);
		INIT_LIST_HEAD(&syncpt->intr.wait_head);
		snprintf(syncpt->intr.thresh_irq_name,
			 sizeof(syncpt->intr.thresh_irq_name),
			 "host1x_sp_%02u", id);
	}

	host1x_intr_start(host);

	return 0;
}