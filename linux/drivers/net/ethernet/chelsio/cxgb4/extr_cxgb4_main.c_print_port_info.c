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
struct TYPE_4__ {int pcaps; } ;
struct port_info {int /*<<< orphan*/  port_type; TYPE_1__ link_cfg; struct adapter* adapter; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_2__ vpd; } ;
struct adapter {int /*<<< orphan*/  name; TYPE_3__ params; } ;

/* Variables and functions */
 int FW_PORT_CAP32_SPEED_100G ; 
 int FW_PORT_CAP32_SPEED_100M ; 
 int FW_PORT_CAP32_SPEED_10G ; 
 int FW_PORT_CAP32_SPEED_1G ; 
 int FW_PORT_CAP32_SPEED_200G ; 
 int FW_PORT_CAP32_SPEED_25G ; 
 int FW_PORT_CAP32_SPEED_400G ; 
 int FW_PORT_CAP32_SPEED_40G ; 
 int FW_PORT_CAP32_SPEED_50G ; 
 int /*<<< orphan*/  netdev_info (struct net_device const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct port_info* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 char* t4_get_port_type_description (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_port_info(const struct net_device *dev)
{
	char buf[80];
	char *bufp = buf;
	const struct port_info *pi = netdev_priv(dev);
	const struct adapter *adap = pi->adapter;

	if (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_100M)
		bufp += sprintf(bufp, "100M/");
	if (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_1G)
		bufp += sprintf(bufp, "1G/");
	if (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_10G)
		bufp += sprintf(bufp, "10G/");
	if (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_25G)
		bufp += sprintf(bufp, "25G/");
	if (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_40G)
		bufp += sprintf(bufp, "40G/");
	if (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_50G)
		bufp += sprintf(bufp, "50G/");
	if (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_100G)
		bufp += sprintf(bufp, "100G/");
	if (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_200G)
		bufp += sprintf(bufp, "200G/");
	if (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_400G)
		bufp += sprintf(bufp, "400G/");
	if (bufp != buf)
		--bufp;
	sprintf(bufp, "BASE-%s", t4_get_port_type_description(pi->port_type));

	netdev_info(dev, "%s: Chelsio %s (%s) %s\n",
		    dev->name, adap->params.vpd.id, adap->name, buf);
}