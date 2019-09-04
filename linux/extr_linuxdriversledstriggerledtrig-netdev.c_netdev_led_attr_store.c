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
struct led_netdev_data {int /*<<< orphan*/  mode; int /*<<< orphan*/  work; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum netdev_led_attr { ____Placeholder_netdev_led_attr } netdev_led_attr ;

/* Variables and functions */
 int EINVAL ; 
#define  NETDEV_ATTR_LINK 130 
#define  NETDEV_ATTR_RX 129 
#define  NETDEV_ATTR_TX 128 
 int NETDEV_LED_LINK ; 
 int NETDEV_LED_RX ; 
 int NETDEV_LED_TX ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct led_netdev_data* led_trigger_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  set_baseline_state (struct led_netdev_data*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t netdev_led_attr_store(struct device *dev, const char *buf,
	size_t size, enum netdev_led_attr attr)
{
	struct led_netdev_data *trigger_data = led_trigger_get_drvdata(dev);
	unsigned long state;
	int ret;
	int bit;

	ret = kstrtoul(buf, 0, &state);
	if (ret)
		return ret;

	switch (attr) {
	case NETDEV_ATTR_LINK:
		bit = NETDEV_LED_LINK;
		break;
	case NETDEV_ATTR_TX:
		bit = NETDEV_LED_TX;
		break;
	case NETDEV_ATTR_RX:
		bit = NETDEV_LED_RX;
		break;
	default:
		return -EINVAL;
	}

	cancel_delayed_work_sync(&trigger_data->work);

	if (state)
		set_bit(bit, &trigger_data->mode);
	else
		clear_bit(bit, &trigger_data->mode);

	set_baseline_state(trigger_data);

	return size;
}