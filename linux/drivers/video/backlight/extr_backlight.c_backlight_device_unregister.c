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
struct backlight_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  ops_lock; int /*<<< orphan*/ * ops; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_UNREGISTERED ; 
 int /*<<< orphan*/  backlight_dev_list_mutex ; 
 int /*<<< orphan*/  backlight_notifier ; 
 int /*<<< orphan*/  backlight_unregister_fb (struct backlight_device*) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct backlight_device*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct backlight_device* pmac_backlight ; 
 int /*<<< orphan*/  pmac_backlight_mutex ; 

void backlight_device_unregister(struct backlight_device *bd)
{
	if (!bd)
		return;

	mutex_lock(&backlight_dev_list_mutex);
	list_del(&bd->entry);
	mutex_unlock(&backlight_dev_list_mutex);

#ifdef CONFIG_PMAC_BACKLIGHT
	mutex_lock(&pmac_backlight_mutex);
	if (pmac_backlight == bd)
		pmac_backlight = NULL;
	mutex_unlock(&pmac_backlight_mutex);
#endif

	blocking_notifier_call_chain(&backlight_notifier,
				     BACKLIGHT_UNREGISTERED, bd);

	mutex_lock(&bd->ops_lock);
	bd->ops = NULL;
	mutex_unlock(&bd->ops_lock);

	backlight_unregister_fb(bd);
	device_unregister(&bd->dev);
}