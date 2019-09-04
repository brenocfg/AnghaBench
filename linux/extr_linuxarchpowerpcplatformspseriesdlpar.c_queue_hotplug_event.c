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
struct work_struct {int dummy; } ;
struct pseries_hp_work {int* rc; struct completion* hp_completion; struct pseries_hp_errorlog* errlog; } ;
struct pseries_hp_errorlog {int dummy; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (struct work_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (struct completion*) ; 
 int /*<<< orphan*/  kfree (struct pseries_hp_errorlog*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct pseries_hp_errorlog*,struct pseries_hp_errorlog*,int) ; 
 int /*<<< orphan*/  pseries_hp_work_fn ; 
 int /*<<< orphan*/  pseries_hp_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,struct work_struct*) ; 

void queue_hotplug_event(struct pseries_hp_errorlog *hp_errlog,
			 struct completion *hotplug_done, int *rc)
{
	struct pseries_hp_work *work;
	struct pseries_hp_errorlog *hp_errlog_copy;

	hp_errlog_copy = kmalloc(sizeof(struct pseries_hp_errorlog),
				 GFP_KERNEL);
	memcpy(hp_errlog_copy, hp_errlog, sizeof(struct pseries_hp_errorlog));

	work = kmalloc(sizeof(struct pseries_hp_work), GFP_KERNEL);
	if (work) {
		INIT_WORK((struct work_struct *)work, pseries_hp_work_fn);
		work->errlog = hp_errlog_copy;
		work->hp_completion = hotplug_done;
		work->rc = rc;
		queue_work(pseries_hp_wq, (struct work_struct *)work);
	} else {
		*rc = -ENOMEM;
		kfree(hp_errlog_copy);
		complete(hotplug_done);
	}
}