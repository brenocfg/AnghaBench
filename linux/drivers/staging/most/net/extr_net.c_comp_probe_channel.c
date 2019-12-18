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
struct net_device {int dummy; } ;
struct net_dev_channel {int linked; int ch_id; } ;
struct net_dev_context {struct net_device* dev; struct net_dev_channel rx; struct net_dev_channel tx; int /*<<< orphan*/  list; struct most_interface* iface; } ;
struct most_interface {int dummy; } ;
struct most_channel_config {scalar_t__ data_type; scalar_t__ direction; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ MOST_CH_ASYNC ; 
 scalar_t__ MOST_CH_TX ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_dev_context* get_net_dev (struct most_interface*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  most_nd_setup ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_devices ; 
 struct net_dev_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  probe_disc_mt ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int comp_probe_channel(struct most_interface *iface, int channel_idx,
			      struct most_channel_config *ccfg, char *name,
			      char *args)
{
	struct net_dev_context *nd;
	struct net_dev_channel *ch;
	struct net_device *dev;
	unsigned long flags;
	int ret = 0;

	if (!iface)
		return -EINVAL;

	if (ccfg->data_type != MOST_CH_ASYNC)
		return -EINVAL;

	mutex_lock(&probe_disc_mt);
	nd = get_net_dev(iface);
	if (!nd) {
		dev = alloc_netdev(sizeof(struct net_dev_context), "meth%d",
				   NET_NAME_UNKNOWN, most_nd_setup);
		if (!dev) {
			ret = -ENOMEM;
			goto unlock;
		}

		nd = netdev_priv(dev);
		nd->iface = iface;
		nd->dev = dev;

		spin_lock_irqsave(&list_lock, flags);
		list_add(&nd->list, &net_devices);
		spin_unlock_irqrestore(&list_lock, flags);

		ch = ccfg->direction == MOST_CH_TX ? &nd->tx : &nd->rx;
	} else {
		ch = ccfg->direction == MOST_CH_TX ? &nd->tx : &nd->rx;
		if (ch->linked) {
			pr_err("direction is allocated\n");
			ret = -EINVAL;
			goto unlock;
		}

		if (register_netdev(nd->dev)) {
			pr_err("register_netdev() failed\n");
			ret = -EINVAL;
			goto unlock;
		}
	}
	ch->ch_id = channel_idx;
	ch->linked = true;

unlock:
	mutex_unlock(&probe_disc_mt);
	return ret;
}