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
typedef  scalar_t__ u32 ;
struct drm_device {int /*<<< orphan*/  vblank_time_lock; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 int DRM_TIMESTAMP_MAXRETRIES ; 
 scalar_t__ __get_vblank_counter (struct drm_device*,unsigned int) ; 
 int drm_get_last_vbltimestamp (struct drm_device*,unsigned int,scalar_t__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_vblank (struct drm_device*,unsigned int,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void drm_reset_vblank_timestamp(struct drm_device *dev, unsigned int pipe)
{
	u32 cur_vblank;
	bool rc;
	ktime_t t_vblank;
	int count = DRM_TIMESTAMP_MAXRETRIES;

	spin_lock(&dev->vblank_time_lock);

	/*
	 * sample the current counter to avoid random jumps
	 * when drm_vblank_enable() applies the diff
	 */
	do {
		cur_vblank = __get_vblank_counter(dev, pipe);
		rc = drm_get_last_vbltimestamp(dev, pipe, &t_vblank, false);
	} while (cur_vblank != __get_vblank_counter(dev, pipe) && --count > 0);

	/*
	 * Only reinitialize corresponding vblank timestamp if high-precision query
	 * available and didn't fail. Otherwise reinitialize delayed at next vblank
	 * interrupt and assign 0 for now, to mark the vblanktimestamp as invalid.
	 */
	if (!rc)
		t_vblank = 0;

	/*
	 * +1 to make sure user will never see the same
	 * vblank counter value before and after a modeset
	 */
	store_vblank(dev, pipe, 1, t_vblank, cur_vblank);

	spin_unlock(&dev->vblank_time_lock);
}