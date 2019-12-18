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
typedef  scalar_t__ u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct niu_parent {scalar_t__ port_phy; int num_ports; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ PORT_PHY_INVALID ; 
 scalar_t__ PORT_PHY_UNKNOWN ; 
 int PORT_TYPE_10G ; 
 struct niu_parent* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int phy_decode (scalar_t__,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t show_port_phy(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct platform_device *plat_dev = to_platform_device(dev);
	struct niu_parent *p = dev_get_platdata(&plat_dev->dev);
	u32 port_phy = p->port_phy;
	char *orig_buf = buf;
	int i;

	if (port_phy == PORT_PHY_UNKNOWN ||
	    port_phy == PORT_PHY_INVALID)
		return 0;

	for (i = 0; i < p->num_ports; i++) {
		const char *type_str;
		int type;

		type = phy_decode(port_phy, i);
		if (type == PORT_TYPE_10G)
			type_str = "10G";
		else
			type_str = "1G";
		buf += sprintf(buf,
			       (i == 0) ? "%s" : " %s",
			       type_str);
	}
	buf += sprintf(buf, "\n");
	return buf - orig_buf;
}