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
struct inode {struct drm_crtc* i_private; } ;
struct file {int dummy; } ;
struct drm_crtc_crc_entry {int dummy; } ;
struct drm_crtc_crc {int opened; size_t values_cnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq; struct drm_crtc_crc_entry* entries; int /*<<< orphan*/ * source; } ;
struct drm_crtc {TYPE_2__* funcs; int /*<<< orphan*/  mutex; TYPE_1__* state; int /*<<< orphan*/  dev; struct drm_crtc_crc crc; } ;
struct TYPE_4__ {int (* set_crc_source ) (struct drm_crtc*,int /*<<< orphan*/ *,size_t*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CRC_ENTRIES_NR ; 
 size_t DRM_MAX_CRC_NR ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  crtc_crc_cleanup (struct drm_crtc_crc*) ; 
 int /*<<< orphan*/  crtc_crc_data_count (struct drm_crtc_crc*) ; 
 scalar_t__ drm_drv_uses_atomic_modeset (int /*<<< orphan*/ ) ; 
 int drm_modeset_lock_single_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock (int /*<<< orphan*/ *) ; 
 struct drm_crtc_crc_entry* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (struct drm_crtc*,int /*<<< orphan*/ *,size_t*) ; 
 int stub2 (struct drm_crtc*,int /*<<< orphan*/ *,size_t*) ; 
 int wait_event_interruptible_lock_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crtc_crc_open(struct inode *inode, struct file *filep)
{
	struct drm_crtc *crtc = inode->i_private;
	struct drm_crtc_crc *crc = &crtc->crc;
	struct drm_crtc_crc_entry *entries = NULL;
	size_t values_cnt;
	int ret = 0;

	if (drm_drv_uses_atomic_modeset(crtc->dev)) {
		ret = drm_modeset_lock_single_interruptible(&crtc->mutex);
		if (ret)
			return ret;

		if (!crtc->state->active)
			ret = -EIO;
		drm_modeset_unlock(&crtc->mutex);

		if (ret)
			return ret;
	}

	spin_lock_irq(&crc->lock);
	if (!crc->opened)
		crc->opened = true;
	else
		ret = -EBUSY;
	spin_unlock_irq(&crc->lock);

	if (ret)
		return ret;

	ret = crtc->funcs->set_crc_source(crtc, crc->source, &values_cnt);
	if (ret)
		goto err;

	if (WARN_ON(values_cnt > DRM_MAX_CRC_NR)) {
		ret = -EINVAL;
		goto err_disable;
	}

	if (WARN_ON(values_cnt == 0)) {
		ret = -EINVAL;
		goto err_disable;
	}

	entries = kcalloc(DRM_CRC_ENTRIES_NR, sizeof(*entries), GFP_KERNEL);
	if (!entries) {
		ret = -ENOMEM;
		goto err_disable;
	}

	spin_lock_irq(&crc->lock);
	crc->entries = entries;
	crc->values_cnt = values_cnt;

	/*
	 * Only return once we got a first frame, so userspace doesn't have to
	 * guess when this particular piece of HW will be ready to start
	 * generating CRCs.
	 */
	ret = wait_event_interruptible_lock_irq(crc->wq,
						crtc_crc_data_count(crc),
						crc->lock);
	spin_unlock_irq(&crc->lock);

	if (ret)
		goto err_disable;

	return 0;

err_disable:
	crtc->funcs->set_crc_source(crtc, NULL, &values_cnt);
err:
	spin_lock_irq(&crc->lock);
	crtc_crc_cleanup(crc);
	spin_unlock_irq(&crc->lock);
	return ret;
}