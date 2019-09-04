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
struct ubi_work {int anchor; int /*<<< orphan*/ * func; } ;
struct ubi_device {int wl_scheduled; int /*<<< orphan*/  wl_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  __schedule_ubi_work (struct ubi_device*,struct ubi_work*) ; 
 struct ubi_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wear_leveling_worker ; 

int ubi_ensure_anchor_pebs(struct ubi_device *ubi)
{
	struct ubi_work *wrk;

	spin_lock(&ubi->wl_lock);
	if (ubi->wl_scheduled) {
		spin_unlock(&ubi->wl_lock);
		return 0;
	}
	ubi->wl_scheduled = 1;
	spin_unlock(&ubi->wl_lock);

	wrk = kmalloc(sizeof(struct ubi_work), GFP_NOFS);
	if (!wrk) {
		spin_lock(&ubi->wl_lock);
		ubi->wl_scheduled = 0;
		spin_unlock(&ubi->wl_lock);
		return -ENOMEM;
	}

	wrk->anchor = 1;
	wrk->func = &wear_leveling_worker;
	__schedule_ubi_work(ubi, wrk);
	return 0;
}