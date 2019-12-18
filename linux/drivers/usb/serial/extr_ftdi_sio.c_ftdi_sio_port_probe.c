#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_port {TYPE_2__* serial; } ;
struct ftdi_sio_quirk {int /*<<< orphan*/  (* port_probe ) (struct ftdi_private*) ;} ;
struct ftdi_private {int latency; int /*<<< orphan*/  cfg_lock; } ;
struct TYPE_4__ {TYPE_1__* interface; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  create_sysfs_attrs (struct usb_serial_port*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ftdi_determine_type (struct usb_serial_port*) ; 
 int ftdi_gpio_init (struct usb_serial_port*) ; 
 int /*<<< orphan*/  ftdi_set_max_packet_size (struct usb_serial_port*) ; 
 struct ftdi_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ read_latency_timer (struct usb_serial_port*) ; 
 int /*<<< orphan*/  stub1 (struct ftdi_private*) ; 
 struct ftdi_sio_quirk* usb_get_serial_data (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct ftdi_private*) ; 
 int /*<<< orphan*/  write_latency_timer (struct usb_serial_port*) ; 

__attribute__((used)) static int ftdi_sio_port_probe(struct usb_serial_port *port)
{
	struct ftdi_private *priv;
	const struct ftdi_sio_quirk *quirk = usb_get_serial_data(port->serial);
	int result;

	priv = kzalloc(sizeof(struct ftdi_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mutex_init(&priv->cfg_lock);

	if (quirk && quirk->port_probe)
		quirk->port_probe(priv);

	usb_set_serial_port_data(port, priv);

	ftdi_determine_type(port);
	ftdi_set_max_packet_size(port);
	if (read_latency_timer(port) < 0)
		priv->latency = 16;
	write_latency_timer(port);
	create_sysfs_attrs(port);

	result = ftdi_gpio_init(port);
	if (result < 0) {
		dev_err(&port->serial->interface->dev,
			"GPIO initialisation failed: %d\n",
			result);
	}

	return 0;
}