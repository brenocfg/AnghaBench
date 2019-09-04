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
struct dvb_net_priv {int /*<<< orphan*/  set_multicast_list_wq; } ;

/* Variables and functions */
 struct dvb_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dvb_net_set_multicast_list (struct net_device *dev)
{
	struct dvb_net_priv *priv = netdev_priv(dev);
	schedule_work(&priv->set_multicast_list_wq);
}