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
struct picolcd_fb_data {int force; int /*<<< orphan*/  lock; struct picolcd_data* picolcd; int /*<<< orphan*/  vbitmap; int /*<<< orphan*/  bpp; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  ready; } ;
struct picolcd_data {int /*<<< orphan*/  hdev; } ;
struct fb_info {int /*<<< orphan*/  lock; struct picolcd_fb_data* par; } ;

/* Variables and functions */
 int HID_OUTPUT_FIFO_SIZE ; 
 int /*<<< orphan*/  hid_hw_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picolcd_fb_reset (struct picolcd_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ picolcd_fb_send_tile (struct picolcd_data*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  picolcd_fb_update_tile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void picolcd_fb_update(struct fb_info *info)
{
	int chip, tile, n;
	unsigned long flags;
	struct picolcd_fb_data *fbdata = info->par;
	struct picolcd_data *data;

	mutex_lock(&info->lock);

	spin_lock_irqsave(&fbdata->lock, flags);
	if (!fbdata->ready && fbdata->picolcd)
		picolcd_fb_reset(fbdata->picolcd, 0);
	spin_unlock_irqrestore(&fbdata->lock, flags);

	/*
	 * Translate the framebuffer into the format needed by the PicoLCD.
	 * See display layout above.
	 * Do this one tile after the other and push those tiles that changed.
	 *
	 * Wait for our IO to complete as otherwise we might flood the queue!
	 */
	n = 0;
	for (chip = 0; chip < 4; chip++)
		for (tile = 0; tile < 8; tile++) {
			if (!fbdata->force && !picolcd_fb_update_tile(
					fbdata->vbitmap, fbdata->bitmap,
					fbdata->bpp, chip, tile))
				continue;
			n += 2;
			if (n >= HID_OUTPUT_FIFO_SIZE / 2) {
				spin_lock_irqsave(&fbdata->lock, flags);
				data = fbdata->picolcd;
				spin_unlock_irqrestore(&fbdata->lock, flags);
				mutex_unlock(&info->lock);
				if (!data)
					return;
				hid_hw_wait(data->hdev);
				mutex_lock(&info->lock);
				n = 0;
			}
			spin_lock_irqsave(&fbdata->lock, flags);
			data = fbdata->picolcd;
			spin_unlock_irqrestore(&fbdata->lock, flags);
			if (!data || picolcd_fb_send_tile(data,
					fbdata->vbitmap, chip, tile))
				goto out;
		}
	fbdata->force = false;
	if (n) {
		spin_lock_irqsave(&fbdata->lock, flags);
		data = fbdata->picolcd;
		spin_unlock_irqrestore(&fbdata->lock, flags);
		mutex_unlock(&info->lock);
		if (data)
			hid_hw_wait(data->hdev);
		return;
	}
out:
	mutex_unlock(&info->lock);
}