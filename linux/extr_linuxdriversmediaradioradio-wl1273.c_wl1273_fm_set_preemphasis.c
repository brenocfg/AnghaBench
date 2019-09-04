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
typedef  int u16 ;
struct wl1273_device {unsigned int preemphasis; struct wl1273_core* core; } ;
struct wl1273_core {scalar_t__ mode; int (* write ) (struct wl1273_core*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
#define  V4L2_PREEMPHASIS_50_uS 130 
#define  V4L2_PREEMPHASIS_75_uS 129 
#define  V4L2_PREEMPHASIS_DISABLED 128 
 scalar_t__ WL1273_MODE_OFF ; 
 scalar_t__ WL1273_MODE_SUSPENDED ; 
 int /*<<< orphan*/  WL1273_PREMPH_SET ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct wl1273_core*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wl1273_fm_set_preemphasis(struct wl1273_device *radio,
				     unsigned int preemphasis)
{
	struct wl1273_core *core = radio->core;
	int r;
	u16 em;

	if (core->mode == WL1273_MODE_OFF ||
	    core->mode == WL1273_MODE_SUSPENDED)
		return -EPERM;

	mutex_lock(&core->lock);

	switch (preemphasis) {
	case V4L2_PREEMPHASIS_DISABLED:
		em = 1;
		break;
	case V4L2_PREEMPHASIS_50_uS:
		em = 0;
		break;
	case V4L2_PREEMPHASIS_75_uS:
		em = 2;
		break;
	default:
		r = -EINVAL;
		goto out;
	}

	r = core->write(core, WL1273_PREMPH_SET, em);
	if (r)
		goto out;

	radio->preemphasis = preemphasis;

out:
	mutex_unlock(&core->lock);
	return r;
}