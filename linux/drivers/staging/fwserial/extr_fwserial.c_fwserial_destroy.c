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
struct kref {int dummy; } ;
struct fwtty_port {int index; int /*<<< orphan*/  port; int /*<<< orphan*/  rx_handler; struct fwtty_port** ports; } ;
struct fw_serial {int index; int /*<<< orphan*/  port; int /*<<< orphan*/  rx_handler; struct fw_serial** ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,int,struct fwtty_port*,int,struct fwtty_port*) ; 
 int /*<<< orphan*/  fw_core_remove_address_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fwtty_port*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int num_ports ; 
 struct fwtty_port** port_table ; 
 int port_table_corrupt ; 
 int /*<<< orphan*/  port_table_lock ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 struct fwtty_port* to_serial (struct kref*,struct kref*) ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fwserial_destroy(struct kref *kref)
{
	struct fw_serial *serial = to_serial(kref, kref);
	struct fwtty_port **ports = serial->ports;
	int j, i = ports[0]->index;

	synchronize_rcu();

	mutex_lock(&port_table_lock);
	for (j = 0; j < num_ports; ++i, ++j) {
		port_table_corrupt |= port_table[i] != ports[j];
		WARN_ONCE(port_table_corrupt, "port_table[%d]: %p != ports[%d]: %p",
			  i, port_table[i], j, ports[j]);

		port_table[i] = NULL;
	}
	mutex_unlock(&port_table_lock);

	for (j = 0; j < num_ports; ++j) {
		fw_core_remove_address_handler(&ports[j]->rx_handler);
		tty_port_destroy(&ports[j]->port);
		kfree(ports[j]);
	}
	kfree(serial);
}