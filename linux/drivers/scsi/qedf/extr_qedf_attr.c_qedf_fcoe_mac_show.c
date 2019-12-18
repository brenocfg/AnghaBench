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
typedef  int u8 ;
typedef  int u32 ;
struct fc_lport {int /*<<< orphan*/  host; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  fc_fcoe_set_mac (int*,int*) ; 
 int fc_host_port_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int*) ; 
 struct fc_lport* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qedf_fcoe_mac_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct fc_lport *lport = shost_priv(class_to_shost(dev));
	u32 port_id;
	u8 lport_src_id[3];
	u8 fcoe_mac[6];

	port_id = fc_host_port_id(lport->host);
	lport_src_id[2] = (port_id & 0x000000FF);
	lport_src_id[1] = (port_id & 0x0000FF00) >> 8;
	lport_src_id[0] = (port_id & 0x00FF0000) >> 16;
	fc_fcoe_set_mac(fcoe_mac, lport_src_id);

	return scnprintf(buf, PAGE_SIZE, "%pM\n", fcoe_mac);
}