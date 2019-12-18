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
struct at91_priv {int mb0_id; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct at91_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t at91_sysfs_show_mb0_id(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct at91_priv *priv = netdev_priv(to_net_dev(dev));

	if (priv->mb0_id & CAN_EFF_FLAG)
		return snprintf(buf, PAGE_SIZE, "0x%08x\n", priv->mb0_id);
	else
		return snprintf(buf, PAGE_SIZE, "0x%03x\n", priv->mb0_id);
}