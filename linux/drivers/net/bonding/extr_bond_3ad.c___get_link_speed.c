#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct slave {scalar_t__ link; int speed; TYPE_3__* dev; TYPE_1__* bond; } ;
struct port {int /*<<< orphan*/  actor_port_number; struct slave* slave; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_2__* dev; } ;

/* Variables and functions */
 scalar_t__ AD_LINK_SPEED_100000MBPS ; 
 scalar_t__ AD_LINK_SPEED_10000MBPS ; 
 scalar_t__ AD_LINK_SPEED_1000MBPS ; 
 scalar_t__ AD_LINK_SPEED_100MBPS ; 
 scalar_t__ AD_LINK_SPEED_10MBPS ; 
 scalar_t__ AD_LINK_SPEED_14000MBPS ; 
 scalar_t__ AD_LINK_SPEED_20000MBPS ; 
 scalar_t__ AD_LINK_SPEED_25000MBPS ; 
 scalar_t__ AD_LINK_SPEED_2500MBPS ; 
 scalar_t__ AD_LINK_SPEED_40000MBPS ; 
 scalar_t__ AD_LINK_SPEED_50000MBPS ; 
 scalar_t__ AD_LINK_SPEED_5000MBPS ; 
 scalar_t__ AD_LINK_SPEED_56000MBPS ; 
 scalar_t__ BOND_LINK_UP ; 
#define  SPEED_10 140 
#define  SPEED_100 139 
#define  SPEED_1000 138 
#define  SPEED_10000 137 
#define  SPEED_100000 136 
#define  SPEED_14000 135 
#define  SPEED_20000 134 
#define  SPEED_2500 133 
#define  SPEED_25000 132 
#define  SPEED_40000 131 
#define  SPEED_5000 130 
#define  SPEED_50000 129 
#define  SPEED_56000 128 
 int SPEED_UNKNOWN ; 
 int /*<<< orphan*/  pr_warn_once (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slave_dbg (TYPE_2__*,TYPE_3__*,char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u16 __get_link_speed(struct port *port)
{
	struct slave *slave = port->slave;
	u16 speed;

	/* this if covers only a special case: when the configuration starts
	 * with link down, it sets the speed to 0.
	 * This is done in spite of the fact that the e100 driver reports 0
	 * to be compatible with MVT in the future.
	 */
	if (slave->link != BOND_LINK_UP)
		speed = 0;
	else {
		switch (slave->speed) {
		case SPEED_10:
			speed = AD_LINK_SPEED_10MBPS;
			break;

		case SPEED_100:
			speed = AD_LINK_SPEED_100MBPS;
			break;

		case SPEED_1000:
			speed = AD_LINK_SPEED_1000MBPS;
			break;

		case SPEED_2500:
			speed = AD_LINK_SPEED_2500MBPS;
			break;

		case SPEED_5000:
			speed = AD_LINK_SPEED_5000MBPS;
			break;

		case SPEED_10000:
			speed = AD_LINK_SPEED_10000MBPS;
			break;

		case SPEED_14000:
			speed = AD_LINK_SPEED_14000MBPS;
			break;

		case SPEED_20000:
			speed = AD_LINK_SPEED_20000MBPS;
			break;

		case SPEED_25000:
			speed = AD_LINK_SPEED_25000MBPS;
			break;

		case SPEED_40000:
			speed = AD_LINK_SPEED_40000MBPS;
			break;

		case SPEED_50000:
			speed = AD_LINK_SPEED_50000MBPS;
			break;

		case SPEED_56000:
			speed = AD_LINK_SPEED_56000MBPS;
			break;

		case SPEED_100000:
			speed = AD_LINK_SPEED_100000MBPS;
			break;

		default:
			/* unknown speed value from ethtool. shouldn't happen */
			if (slave->speed != SPEED_UNKNOWN)
				pr_warn_once("%s: (slave %s): unknown ethtool speed (%d) for port %d (set it to 0)\n",
					     slave->bond->dev->name,
					     slave->dev->name, slave->speed,
					     port->actor_port_number);
			speed = 0;
			break;
		}
	}

	slave_dbg(slave->bond->dev, slave->dev, "Port %d Received link speed %d update from adapter\n",
		  port->actor_port_number, speed);
	return speed;
}