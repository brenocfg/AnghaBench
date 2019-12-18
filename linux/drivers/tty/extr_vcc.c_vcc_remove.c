#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct vio_dev {TYPE_2__ dev; } ;
struct TYPE_4__ {struct vcc_port* name; int /*<<< orphan*/  timer; } ;
struct vcc_port {int removed; struct vcc_port* domain; TYPE_1__ vio; int /*<<< orphan*/  index; scalar_t__ tty; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  rx_timer; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct vcc_port* dev_get_drvdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vcc_port*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_vhangup (scalar_t__) ; 
 int /*<<< orphan*/  vcc_attribute_group ; 
 struct vcc_port* vcc_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcc_put (struct vcc_port*,int) ; 
 int /*<<< orphan*/  vcc_table_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcc_tty_driver ; 
 int /*<<< orphan*/  vio_ldc_free (TYPE_1__*) ; 

__attribute__((used)) static int vcc_remove(struct vio_dev *vdev)
{
	struct vcc_port *port = dev_get_drvdata(&vdev->dev);

	if (!port)
		return -ENODEV;

	del_timer_sync(&port->rx_timer);
	del_timer_sync(&port->tx_timer);

	/* If there's a process with the device open, do a synchronous
	 * hangup of the TTY. This *may* cause the process to call close
	 * asynchronously, but it's not guaranteed.
	 */
	if (port->tty)
		tty_vhangup(port->tty);

	/* Get exclusive reference to VCC, ensures that there are no other
	 * clients to this port
	 */
	port = vcc_get(port->index, true);

	if (WARN_ON(!port))
		return -ENODEV;

	tty_unregister_device(vcc_tty_driver, port->index);

	del_timer_sync(&port->vio.timer);
	vio_ldc_free(&port->vio);
	sysfs_remove_group(&vdev->dev.kobj, &vcc_attribute_group);
	dev_set_drvdata(&vdev->dev, NULL);
	if (port->tty) {
		port->removed = true;
		vcc_put(port, true);
	} else {
		vcc_table_remove(port->index);

		kfree(port->vio.name);
		kfree(port->domain);
		kfree(port);
	}

	return 0;
}