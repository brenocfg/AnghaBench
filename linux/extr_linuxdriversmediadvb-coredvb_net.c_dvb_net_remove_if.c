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
struct net_device {int /*<<< orphan*/  name; } ;
struct dvb_net_priv {int /*<<< orphan*/  restart_net_feed_wq; int /*<<< orphan*/  set_multicast_list_wq; scalar_t__ in_use; } ;
struct dvb_net {struct net_device** device; scalar_t__* state; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  dvb_net_stop (struct net_device*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct dvb_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int dvb_net_remove_if(struct dvb_net *dvbnet, unsigned long num)
{
	struct net_device *net = dvbnet->device[num];
	struct dvb_net_priv *priv;

	if (!dvbnet->state[num])
		return -EINVAL;
	priv = netdev_priv(net);
	if (priv->in_use)
		return -EBUSY;

	dvb_net_stop(net);
	flush_work(&priv->set_multicast_list_wq);
	flush_work(&priv->restart_net_feed_wq);
	pr_info("removed network interface %s\n", net->name);
	unregister_netdev(net);
	dvbnet->state[num]=0;
	dvbnet->device[num] = NULL;
	free_netdev(net);

	return 0;
}