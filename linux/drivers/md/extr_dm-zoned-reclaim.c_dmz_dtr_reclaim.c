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
struct dmz_reclaim {int /*<<< orphan*/  kc; int /*<<< orphan*/  wq; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_kcopyd_client_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dmz_reclaim*) ; 

void dmz_dtr_reclaim(struct dmz_reclaim *zrc)
{
	cancel_delayed_work_sync(&zrc->work);
	destroy_workqueue(zrc->wq);
	dm_kcopyd_client_destroy(zrc->kc);
	kfree(zrc);
}