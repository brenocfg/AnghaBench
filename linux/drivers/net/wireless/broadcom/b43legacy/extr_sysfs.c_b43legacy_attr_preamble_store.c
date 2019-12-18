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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct b43legacy_wldev {int short_preamble; TYPE_1__* wl; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct b43legacy_wldev* dev_to_b43legacy_wldev (struct device*) ; 
 int get_boolean (char const*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t b43legacy_attr_preamble_store(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf, size_t count)
{
	struct b43legacy_wldev *wldev = dev_to_b43legacy_wldev(dev);
	unsigned long flags;
	int value;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	value = get_boolean(buf, count);
	if (value < 0)
		return value;
	mutex_lock(&wldev->wl->mutex);
	spin_lock_irqsave(&wldev->wl->irq_lock, flags);

	wldev->short_preamble = !!value;

	spin_unlock_irqrestore(&wldev->wl->irq_lock, flags);
	mutex_unlock(&wldev->wl->mutex);

	return count;
}