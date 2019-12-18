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
struct netdev_private {int dspcfg_workaround; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct netdev_private* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,size_t) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t natsemi_set_dspcfg_workaround(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf, size_t count)
{
	struct netdev_private *np = netdev_priv(to_net_dev(dev));
	int new_setting;
	unsigned long flags;

        /* Find out the new setting */
        if (!strncmp("on", buf, count - 1) || !strncmp("1", buf, count - 1))
                new_setting = 1;
        else if (!strncmp("off", buf, count - 1) ||
                 !strncmp("0", buf, count - 1))
		new_setting = 0;
	else
                 return count;

	spin_lock_irqsave(&np->lock, flags);

	np->dspcfg_workaround = new_setting;

	spin_unlock_irqrestore(&np->lock, flags);

	return count;
}