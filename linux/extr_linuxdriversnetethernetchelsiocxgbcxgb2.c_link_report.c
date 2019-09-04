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
struct TYPE_2__ {int speed; scalar_t__ duplex; } ;
struct port_info {TYPE_1__ link_config; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_10000 128 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void link_report(struct port_info *p)
{
	if (!netif_carrier_ok(p->dev))
		netdev_info(p->dev, "link down\n");
	else {
		const char *s = "10Mbps";

		switch (p->link_config.speed) {
			case SPEED_10000: s = "10Gbps"; break;
			case SPEED_1000:  s = "1000Mbps"; break;
			case SPEED_100:   s = "100Mbps"; break;
		}

		netdev_info(p->dev, "link up, %s, %s-duplex\n",
			    s, p->link_config.duplex == DUPLEX_FULL
			    ? "full" : "half");
	}
}