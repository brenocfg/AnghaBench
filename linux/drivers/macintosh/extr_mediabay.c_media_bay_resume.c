#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct media_bay_info {scalar_t__ content_id; scalar_t__ last_value; scalar_t__ state; int /*<<< orphan*/  lock; scalar_t__ sleeping; int /*<<< orphan*/  index; void* timer; void* value_count; TYPE_4__* ops; } ;
struct TYPE_10__ {scalar_t__ event; } ;
struct TYPE_6__ {TYPE_5__ power_state; } ;
struct TYPE_7__ {TYPE_1__ power; } ;
struct TYPE_8__ {TYPE_2__ dev; } ;
struct macio_dev {TYPE_3__ ofdev; } ;
struct TYPE_9__ {scalar_t__ (* content ) (struct media_bay_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MB_POLL_DELAY ; 
 int /*<<< orphan*/  MB_POWER_DELAY ; 
 int /*<<< orphan*/  MB_STABLE_DELAY ; 
 TYPE_5__ PMSG_ON ; 
 scalar_t__ PM_EVENT_ON ; 
 struct media_bay_info* macio_get_drvdata (struct macio_dev*) ; 
 scalar_t__ mb_empty ; 
 scalar_t__ mb_up ; 
 int /*<<< orphan*/  media_bay_step (int /*<<< orphan*/ ) ; 
 void* msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mb_power (struct media_bay_info*,int) ; 
 scalar_t__ stub1 (struct media_bay_info*) ; 

__attribute__((used)) static int media_bay_resume(struct macio_dev *mdev)
{
	struct media_bay_info	*bay = macio_get_drvdata(mdev);

	if (mdev->ofdev.dev.power.power_state.event != PM_EVENT_ON) {
		mdev->ofdev.dev.power.power_state = PMSG_ON;

	       	/* We re-enable the bay using it's previous content
	       	   only if it did not change. Note those bozo timings,
	       	   they seem to help the 3400 get it right.
	       	 */
	       	/* Force MB power to 0 */
		mutex_lock(&bay->lock);
	       	set_mb_power(bay, 0);
		msleep(MB_POWER_DELAY);
	       	if (bay->ops->content(bay) != bay->content_id) {
			printk("mediabay%d: Content changed during sleep...\n", bay->index);
			mutex_unlock(&bay->lock);
	       		return 0;
		}
	       	set_mb_power(bay, 1);
	       	bay->last_value = bay->content_id;
	       	bay->value_count = msecs_to_jiffies(MB_STABLE_DELAY);
	       	bay->timer = msecs_to_jiffies(MB_POWER_DELAY);
	       	do {
			msleep(MB_POLL_DELAY);
	       		media_bay_step(bay->index);
	       	} while((bay->state != mb_empty) &&
	       		(bay->state != mb_up));
		bay->sleeping = 0;
		mutex_unlock(&bay->lock);
	}
	return 0;
}