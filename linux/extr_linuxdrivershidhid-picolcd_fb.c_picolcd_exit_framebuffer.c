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
struct picolcd_fb_data {int /*<<< orphan*/  lock; int /*<<< orphan*/ * picolcd; } ;
struct picolcd_data {struct fb_info* fb_info; TYPE_1__* hdev; } ;
struct fb_info {int /*<<< orphan*/  deferred_work; struct picolcd_fb_data* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_fb_update_rate ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

void picolcd_exit_framebuffer(struct picolcd_data *data)
{
	struct fb_info *info = data->fb_info;
	struct picolcd_fb_data *fbdata;
	unsigned long flags;

	if (!info)
		return;

	device_remove_file(&data->hdev->dev, &dev_attr_fb_update_rate);
	fbdata = info->par;

	/* disconnect framebuffer from HID dev */
	spin_lock_irqsave(&fbdata->lock, flags);
	fbdata->picolcd = NULL;
	spin_unlock_irqrestore(&fbdata->lock, flags);

	/* make sure there is no running update - thus that fbdata->picolcd
	 * once obtained under lock is guaranteed not to get free() under
	 * the feet of the deferred work */
	flush_delayed_work(&info->deferred_work);

	data->fb_info = NULL;
	unregister_framebuffer(info);
}