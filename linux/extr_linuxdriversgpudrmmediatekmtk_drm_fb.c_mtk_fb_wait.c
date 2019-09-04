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
struct reservation_object {int dummy; } ;
struct drm_gem_object {TYPE_1__* dma_buf; } ;
struct drm_framebuffer {struct drm_gem_object** obj; } ;
struct TYPE_2__ {struct reservation_object* resv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 scalar_t__ WARN_ON (int) ; 
 long reservation_object_wait_timeout_rcu (struct reservation_object*,int,int,int /*<<< orphan*/ ) ; 

int mtk_fb_wait(struct drm_framebuffer *fb)
{
	struct drm_gem_object *gem;
	struct reservation_object *resv;
	long ret;

	if (!fb)
		return 0;

	gem = fb->obj[0];
	if (!gem || !gem->dma_buf || !gem->dma_buf->resv)
		return 0;

	resv = gem->dma_buf->resv;
	ret = reservation_object_wait_timeout_rcu(resv, false, true,
						  MAX_SCHEDULE_TIMEOUT);
	/* MAX_SCHEDULE_TIMEOUT on success, -ERESTARTSYS if interrupted */
	if (WARN_ON(ret < 0))
		return ret;

	return 0;
}