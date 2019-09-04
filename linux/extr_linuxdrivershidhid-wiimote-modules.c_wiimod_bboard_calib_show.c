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
struct TYPE_2__ {size_t** calib_bboard; int /*<<< orphan*/  lock; } ;
struct wiimote_data {TYPE_1__ state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  size_t __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int EIO ; 
 struct wiimote_data* dev_to_wii (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ sprintf (char*,char*,int) ; 
 int wiimote_cmd_acquire (struct wiimote_data*) ; 
 int wiimote_cmd_read (struct wiimote_data*,int,size_t*,int) ; 
 int /*<<< orphan*/  wiimote_cmd_release (struct wiimote_data*) ; 

__attribute__((used)) static ssize_t wiimod_bboard_calib_show(struct device *dev,
					struct device_attribute *attr,
					char *out)
{
	struct wiimote_data *wdata = dev_to_wii(dev);
	int i, j, ret;
	__u16 val;
	__u8 buf[24], offs;

	ret = wiimote_cmd_acquire(wdata);
	if (ret)
		return ret;

	ret = wiimote_cmd_read(wdata, 0xa40024, buf, 12);
	if (ret != 12) {
		wiimote_cmd_release(wdata);
		return ret < 0 ? ret : -EIO;
	}
	ret = wiimote_cmd_read(wdata, 0xa40024 + 12, buf + 12, 12);
	if (ret != 12) {
		wiimote_cmd_release(wdata);
		return ret < 0 ? ret : -EIO;
	}

	wiimote_cmd_release(wdata);

	spin_lock_irq(&wdata->state.lock);
	offs = 0;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 4; ++j) {
			wdata->state.calib_bboard[j][i] = buf[offs];
			wdata->state.calib_bboard[j][i] <<= 8;
			wdata->state.calib_bboard[j][i] |= buf[offs + 1];
			offs += 2;
		}
	}
	spin_unlock_irq(&wdata->state.lock);

	ret = 0;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 4; ++j) {
			val = wdata->state.calib_bboard[j][i];
			if (i == 2 && j == 3)
				ret += sprintf(&out[ret], "%04x\n", val);
			else
				ret += sprintf(&out[ret], "%04x:", val);
		}
	}

	return ret;
}