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
struct softing_priv {unsigned long output; struct softing* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct softing {TYPE_1__ fw; } ;
struct net_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int ERESTARTSYS ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct softing_priv* netdev2softing (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct net_device* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t store_output(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct net_device *ndev = to_net_dev(dev);
	struct softing_priv *priv = netdev2softing(ndev);
	struct softing *card = priv->card;
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 0, &val);
	if (ret < 0)
		return ret;
	val &= 0xFF;

	ret = mutex_lock_interruptible(&card->fw.lock);
	if (ret)
		return -ERESTARTSYS;
	if (netif_running(ndev)) {
		mutex_unlock(&card->fw.lock);
		return -EBUSY;
	}
	priv->output = val;
	mutex_unlock(&card->fw.lock);
	return count;
}