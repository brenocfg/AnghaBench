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
struct gb_interface {int active; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gb_interface_activate (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_interface_deactivate (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_interface_disable (struct gb_interface*) ; 
 int gb_interface_enable (struct gb_interface*) ; 
 scalar_t__ kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gb_interface* to_gb_interface (struct device*) ; 

__attribute__((used)) static ssize_t power_state_store(struct device *dev,
				 struct device_attribute *attr, const char *buf,
				 size_t len)
{
	struct gb_interface *intf = to_gb_interface(dev);
	bool activate;
	int ret = 0;

	if (kstrtobool(buf, &activate))
		return -EINVAL;

	mutex_lock(&intf->mutex);

	if (activate == intf->active)
		goto unlock;

	if (activate) {
		ret = gb_interface_activate(intf);
		if (ret) {
			dev_err(&intf->dev,
				"failed to activate interface: %d\n", ret);
			goto unlock;
		}

		ret = gb_interface_enable(intf);
		if (ret) {
			dev_err(&intf->dev,
				"failed to enable interface: %d\n", ret);
			gb_interface_deactivate(intf);
			goto unlock;
		}
	} else {
		gb_interface_disable(intf);
		gb_interface_deactivate(intf);
	}

unlock:
	mutex_unlock(&intf->mutex);

	if (ret)
		return ret;

	return len;
}