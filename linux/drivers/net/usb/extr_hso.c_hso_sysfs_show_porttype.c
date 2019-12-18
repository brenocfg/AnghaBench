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
struct hso_device {int port_spec; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  HSO_PORT_APP 137 
#define  HSO_PORT_APP2 136 
#define  HSO_PORT_CONTROL 135 
#define  HSO_PORT_DIAG 134 
#define  HSO_PORT_DIAG2 133 
#define  HSO_PORT_GPS 132 
#define  HSO_PORT_GPS_CONTROL 131 
 int HSO_PORT_MASK ; 
#define  HSO_PORT_MODEM 130 
#define  HSO_PORT_NETWORK 129 
#define  HSO_PORT_PCSC 128 
 struct hso_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t hso_sysfs_show_porttype(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	struct hso_device *hso_dev = dev_get_drvdata(dev);
	char *port_name;

	if (!hso_dev)
		return 0;

	switch (hso_dev->port_spec & HSO_PORT_MASK) {
	case HSO_PORT_CONTROL:
		port_name = "Control";
		break;
	case HSO_PORT_APP:
		port_name = "Application";
		break;
	case HSO_PORT_APP2:
		port_name = "Application2";
		break;
	case HSO_PORT_GPS:
		port_name = "GPS";
		break;
	case HSO_PORT_GPS_CONTROL:
		port_name = "GPS Control";
		break;
	case HSO_PORT_PCSC:
		port_name = "PCSC";
		break;
	case HSO_PORT_DIAG:
		port_name = "Diagnostic";
		break;
	case HSO_PORT_DIAG2:
		port_name = "Diagnostic2";
		break;
	case HSO_PORT_MODEM:
		port_name = "Modem";
		break;
	case HSO_PORT_NETWORK:
		port_name = "Network";
		break;
	default:
		port_name = "Unknown";
		break;
	}

	return sprintf(buf, "%s\n", port_name);
}