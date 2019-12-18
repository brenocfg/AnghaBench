#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_rect {void* y2; void* x2; void* y1; void* x1; } ;
struct TYPE_4__ {int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; struct drm_rect rect; struct drm_framebuffer* fb; } ;
struct gm12u320_device {TYPE_2__ fb_update; } ;
struct drm_framebuffer {TYPE_1__* dev; } ;
struct TYPE_3__ {struct gm12u320_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_get (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_framebuffer_put (struct drm_framebuffer*) ; 
 void* max (void*,void*) ; 
 void* min (void*,void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gm12u320_fb_mark_dirty(struct drm_framebuffer *fb,
				   struct drm_rect *dirty)
{
	struct gm12u320_device *gm12u320 = fb->dev->dev_private;
	struct drm_framebuffer *old_fb = NULL;
	bool wakeup = false;

	mutex_lock(&gm12u320->fb_update.lock);

	if (gm12u320->fb_update.fb != fb) {
		old_fb = gm12u320->fb_update.fb;
		drm_framebuffer_get(fb);
		gm12u320->fb_update.fb = fb;
		gm12u320->fb_update.rect = *dirty;
		wakeup = true;
	} else {
		struct drm_rect *rect = &gm12u320->fb_update.rect;

		rect->x1 = min(rect->x1, dirty->x1);
		rect->y1 = min(rect->y1, dirty->y1);
		rect->x2 = max(rect->x2, dirty->x2);
		rect->y2 = max(rect->y2, dirty->y2);
	}

	mutex_unlock(&gm12u320->fb_update.lock);

	if (wakeup)
		wake_up(&gm12u320->fb_update.waitq);

	if (old_fb)
		drm_framebuffer_put(old_fb);
}