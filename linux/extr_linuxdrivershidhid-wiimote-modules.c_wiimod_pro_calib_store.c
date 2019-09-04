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
struct TYPE_2__ {void** calib_pro_sticks; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct wiimote_data {TYPE_1__ state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  void* s16 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  WIIPROTO_FLAG_PRO_CALIB_DONE ; 
 struct wiimote_data* dev_to_wii (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,void**,void**,void**,void**) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strnlen (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t wiimod_pro_calib_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct wiimote_data *wdata = dev_to_wii(dev);
	int r;
	s16 x1, y1, x2, y2;

	if (!strncmp(buf, "scan\n", 5)) {
		spin_lock_irq(&wdata->state.lock);
		wdata->state.flags &= ~WIIPROTO_FLAG_PRO_CALIB_DONE;
		spin_unlock_irq(&wdata->state.lock);
	} else {
		r = sscanf(buf, "%hd:%hd %hd:%hd", &x1, &y1, &x2, &y2);
		if (r != 4)
			return -EINVAL;

		spin_lock_irq(&wdata->state.lock);
		wdata->state.flags |= WIIPROTO_FLAG_PRO_CALIB_DONE;
		spin_unlock_irq(&wdata->state.lock);

		wdata->state.calib_pro_sticks[0] = x1;
		wdata->state.calib_pro_sticks[1] = y1;
		wdata->state.calib_pro_sticks[2] = x2;
		wdata->state.calib_pro_sticks[3] = y2;
	}

	return strnlen(buf, PAGE_SIZE);
}