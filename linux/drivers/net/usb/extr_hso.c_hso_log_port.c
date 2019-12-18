#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hso_device {int port_spec; TYPE_2__* interface; } ;
struct TYPE_8__ {TYPE_1__* net; } ;
struct TYPE_7__ {int /*<<< orphan*/  minor; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {char* name; } ;

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
 TYPE_4__* dev2net (struct hso_device*) ; 
 TYPE_3__* dev2ser (struct hso_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 char* tty_filename ; 

__attribute__((used)) static void hso_log_port(struct hso_device *hso_dev)
{
	char *port_type;
	char port_dev[20];

	switch (hso_dev->port_spec & HSO_PORT_MASK) {
	case HSO_PORT_CONTROL:
		port_type = "Control";
		break;
	case HSO_PORT_APP:
		port_type = "Application";
		break;
	case HSO_PORT_GPS:
		port_type = "GPS";
		break;
	case HSO_PORT_GPS_CONTROL:
		port_type = "GPS control";
		break;
	case HSO_PORT_APP2:
		port_type = "Application2";
		break;
	case HSO_PORT_PCSC:
		port_type = "PCSC";
		break;
	case HSO_PORT_DIAG:
		port_type = "Diagnostic";
		break;
	case HSO_PORT_DIAG2:
		port_type = "Diagnostic2";
		break;
	case HSO_PORT_MODEM:
		port_type = "Modem";
		break;
	case HSO_PORT_NETWORK:
		port_type = "Network";
		break;
	default:
		port_type = "Unknown";
		break;
	}
	if ((hso_dev->port_spec & HSO_PORT_MASK) == HSO_PORT_NETWORK) {
		sprintf(port_dev, "%s", dev2net(hso_dev)->net->name);
	} else
		sprintf(port_dev, "/dev/%s%d", tty_filename,
			dev2ser(hso_dev)->minor);

	dev_dbg(&hso_dev->interface->dev, "HSO: Found %s port %s\n",
		port_type, port_dev);
}