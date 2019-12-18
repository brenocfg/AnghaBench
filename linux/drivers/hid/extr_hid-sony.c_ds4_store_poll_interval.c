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
typedef  scalar_t__ u8 ;
struct sony_sc {int /*<<< orphan*/  lock; scalar_t__ ds4_bt_poll_interval; } ;
struct hid_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ DS4_BT_MAX_POLL_INTERVAL_MS ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  SONY_WORKER_STATE ; 
 struct sony_sc* hid_get_drvdata (struct hid_device*) ; 
 scalar_t__ kstrtou8 (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sony_schedule_work (struct sony_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static ssize_t ds4_store_poll_interval(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct hid_device *hdev = to_hid_device(dev);
	struct sony_sc *sc = hid_get_drvdata(hdev);
	unsigned long flags;
	u8 interval;

	if (kstrtou8(buf, 0, &interval))
		return -EINVAL;

	if (interval > DS4_BT_MAX_POLL_INTERVAL_MS)
		return -EINVAL;

	spin_lock_irqsave(&sc->lock, flags);
	sc->ds4_bt_poll_interval = interval;
	spin_unlock_irqrestore(&sc->lock, flags);

	sony_schedule_work(sc, SONY_WORKER_STATE);

	return count;
}