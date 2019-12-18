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
struct netdev_phys_item_id {int id_len; int /*<<< orphan*/ * id; } ;
struct net_device {int dummy; } ;
struct ethsw_port_priv {TYPE_1__* ethsw_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_id; } ;

/* Variables and functions */
 struct ethsw_port_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int swdev_get_port_parent_id(struct net_device *dev,
				    struct netdev_phys_item_id *ppid)
{
	struct ethsw_port_priv *port_priv = netdev_priv(dev);

	ppid->id_len = 1;
	ppid->id[0] = port_priv->ethsw_data->dev_id;

	return 0;
}