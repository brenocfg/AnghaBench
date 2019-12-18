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
typedef  int u_char ;
struct pcnet_dev {int flags; } ;
struct net_device {int if_port; } ;
struct ifmap {int port; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int HAS_MISC_REG ; 
 int /*<<< orphan*/  NS8390_init (struct net_device*,int) ; 
 struct pcnet_dev* PRIV (struct net_device*) ; 
 int /*<<< orphan*/ * if_names ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_config(struct net_device *dev, struct ifmap *map)
{
    struct pcnet_dev *info = PRIV(dev);
    if ((map->port != (u_char)(-1)) && (map->port != dev->if_port)) {
	if (!(info->flags & HAS_MISC_REG))
	    return -EOPNOTSUPP;
	else if ((map->port < 1) || (map->port > 2))
	    return -EINVAL;
	dev->if_port = map->port;
	netdev_info(dev, "switched to %s port\n", if_names[dev->if_port]);
	NS8390_init(dev, 1);
    }
    return 0;
}