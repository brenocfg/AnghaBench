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
struct TYPE_2__ {int speed; size_t fc; } ;
struct port_info {TYPE_1__ link_cfg; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void link_report(struct net_device *dev)
{
	if (!netif_carrier_ok(dev))
		netdev_info(dev, "link down\n");
	else {
		static const char *fc[] = { "no", "Rx", "Tx", "Tx/Rx" };

		const char *s;
		const struct port_info *p = netdev_priv(dev);

		switch (p->link_cfg.speed) {
		case 100:
			s = "100Mbps";
			break;
		case 1000:
			s = "1Gbps";
			break;
		case 10000:
			s = "10Gbps";
			break;
		case 25000:
			s = "25Gbps";
			break;
		case 40000:
			s = "40Gbps";
			break;
		case 50000:
			s = "50Gbps";
			break;
		case 100000:
			s = "100Gbps";
			break;
		default:
			pr_info("%s: unsupported speed: %d\n",
				dev->name, p->link_cfg.speed);
			return;
		}

		netdev_info(dev, "link up, %s, full-duplex, %s PAUSE\n", s,
			    fc[p->link_cfg.fc]);
	}
}