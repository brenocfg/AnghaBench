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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_ATTR_TX ; 
 int /*<<< orphan*/  netdev_led_attr_show (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t tx_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	return netdev_led_attr_show(dev, buf, NETDEV_ATTR_TX);
}