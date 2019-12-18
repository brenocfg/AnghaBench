#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_7__ {struct fwtty_port* callback_data; int /*<<< orphan*/  address_callback; scalar_t__ length; } ;
struct fwtty_port {int loopback; struct fwtty_port** ports; TYPE_1__ port; int /*<<< orphan*/  kref; int /*<<< orphan*/  index; int /*<<< orphan*/  list; int /*<<< orphan*/  debugfs; struct device* device; TYPE_5__ rx_handler; int /*<<< orphan*/  peer; int /*<<< orphan*/  tx_fifo; int /*<<< orphan*/  max_payload; int /*<<< orphan*/  wait_tx; int /*<<< orphan*/  hangup; int /*<<< orphan*/  emit_breaks; int /*<<< orphan*/  drain; int /*<<< orphan*/  lock; struct fwtty_port* serial; int /*<<< orphan*/  peer_list; struct fw_card* card; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;
struct fw_serial {int loopback; struct fw_serial** ports; TYPE_1__ port; int /*<<< orphan*/  kref; int /*<<< orphan*/  index; int /*<<< orphan*/  list; int /*<<< orphan*/  debugfs; struct device* device; TYPE_5__ rx_handler; int /*<<< orphan*/  peer; int /*<<< orphan*/  tx_fifo; int /*<<< orphan*/  max_payload; int /*<<< orphan*/  wait_tx; int /*<<< orphan*/  hangup; int /*<<< orphan*/  emit_breaks; int /*<<< orphan*/  drain; int /*<<< orphan*/  lock; struct fw_serial* serial; int /*<<< orphan*/  peer_list; struct fw_card* card; } ;
struct fw_device {struct fw_card* card; } ;
struct fw_card {scalar_t__ guid; int /*<<< orphan*/ * device; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FWTTY_INVALID_INDEX ; 
 scalar_t__ FWTTY_PORT_RXFIFO_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCODE_100 ; 
 scalar_t__ create_loop_dev ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct fwtty_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fifo_init (int /*<<< orphan*/ *) ; 
 int fw_core_add_address_handler (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_high_memory_region ; 
 struct fw_device* fw_parent_device (struct fw_unit*) ; 
 int /*<<< orphan*/  fwloop_driver ; 
 int fwserial_add_peer (struct fwtty_port*,struct fw_unit*) ; 
 int /*<<< orphan*/  fwserial_debugfs ; 
 int /*<<< orphan*/  fwserial_destroy ; 
 int /*<<< orphan*/  fwserial_list ; 
 int /*<<< orphan*/  fwtty_do_hangup ; 
 int /*<<< orphan*/  fwtty_drain_tx ; 
 int /*<<< orphan*/  fwtty_driver ; 
 int /*<<< orphan*/  fwtty_emit_breaks ; 
 int /*<<< orphan*/  fwtty_err (struct fw_unit**,char*,...) ; 
 int /*<<< orphan*/  fwtty_notice (struct fw_unit**,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  fwtty_peers_fops ; 
 int /*<<< orphan*/  fwtty_port_handler ; 
 int /*<<< orphan*/  fwtty_port_ops ; 
 int fwtty_ports_add (struct fwtty_port*) ; 
 int /*<<< orphan*/  fwtty_stats_fops ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fwtty_port*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fwtty_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_speed_to_max_payload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop_idx (struct fwtty_port*) ; 
 int num_ports ; 
 int num_ttys ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_buffer_set_limit (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tty_port_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_port_init (TYPE_1__*) ; 
 struct device* tty_port_register_device (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fwserial_create(struct fw_unit *unit)
{
	struct fw_device *parent = fw_parent_device(unit);
	struct fw_card *card = parent->card;
	struct fw_serial *serial;
	struct fwtty_port *port;
	struct device *tty_dev;
	int i, j;
	int err;

	serial = kzalloc(sizeof(*serial), GFP_KERNEL);
	if (!serial)
		return -ENOMEM;

	kref_init(&serial->kref);
	serial->card = card;
	INIT_LIST_HEAD(&serial->peer_list);

	for (i = 0; i < num_ports; ++i) {
		port = kzalloc(sizeof(*port), GFP_KERNEL);
		if (!port) {
			err = -ENOMEM;
			goto free_ports;
		}
		tty_port_init(&port->port);
		port->index = FWTTY_INVALID_INDEX;
		port->port.ops = &fwtty_port_ops;
		port->serial = serial;
		tty_buffer_set_limit(&port->port, 128 * 1024);

		spin_lock_init(&port->lock);
		INIT_DELAYED_WORK(&port->drain, fwtty_drain_tx);
		INIT_DELAYED_WORK(&port->emit_breaks, fwtty_emit_breaks);
		INIT_WORK(&port->hangup, fwtty_do_hangup);
		init_waitqueue_head(&port->wait_tx);
		port->max_payload = link_speed_to_max_payload(SCODE_100);
		dma_fifo_init(&port->tx_fifo);

		RCU_INIT_POINTER(port->peer, NULL);
		serial->ports[i] = port;

		/* get unique bus addr region for port's status & recv fifo */
		port->rx_handler.length = FWTTY_PORT_RXFIFO_LEN + 4;
		port->rx_handler.address_callback = fwtty_port_handler;
		port->rx_handler.callback_data = port;
		/*
		 * XXX: use custom memory region above cpu physical memory addrs
		 * this will ease porting to 64-bit firewire adapters
		 */
		err = fw_core_add_address_handler(&port->rx_handler,
						  &fw_high_memory_region);
		if (err) {
			kfree(port);
			goto free_ports;
		}
	}
	/* preserve i for error cleanup */

	err = fwtty_ports_add(serial);
	if (err) {
		fwtty_err(&unit, "no space in port table\n");
		goto free_ports;
	}

	for (j = 0; j < num_ttys; ++j) {
		tty_dev = tty_port_register_device(&serial->ports[j]->port,
						   fwtty_driver,
						   serial->ports[j]->index,
						   card->device);
		if (IS_ERR(tty_dev)) {
			err = PTR_ERR(tty_dev);
			fwtty_err(&unit, "register tty device error (%d)\n",
				  err);
			goto unregister_ttys;
		}

		serial->ports[j]->device = tty_dev;
	}
	/* preserve j for error cleanup */

	if (create_loop_dev) {
		struct device *loop_dev;

		loop_dev = tty_port_register_device(&serial->ports[j]->port,
						    fwloop_driver,
						    loop_idx(serial->ports[j]),
						    card->device);
		if (IS_ERR(loop_dev)) {
			err = PTR_ERR(loop_dev);
			fwtty_err(&unit, "create loop device failed (%d)\n",
				  err);
			goto unregister_ttys;
		}
		serial->ports[j]->device = loop_dev;
		serial->ports[j]->loopback = true;
	}

	if (!IS_ERR_OR_NULL(fwserial_debugfs)) {
		serial->debugfs = debugfs_create_dir(dev_name(&unit->device),
						     fwserial_debugfs);
		if (!IS_ERR_OR_NULL(serial->debugfs)) {
			debugfs_create_file("peers", 0444, serial->debugfs,
					    serial, &fwtty_peers_fops);
			debugfs_create_file("stats", 0444, serial->debugfs,
					    serial, &fwtty_stats_fops);
		}
	}

	list_add_rcu(&serial->list, &fwserial_list);

	fwtty_notice(&unit, "TTY over FireWire on device %s (guid %016llx)\n",
		     dev_name(card->device), (unsigned long long)card->guid);

	err = fwserial_add_peer(serial, unit);
	if (!err)
		return 0;

	fwtty_err(&unit, "unable to add peer unit device (%d)\n", err);

	/* fall-through to error processing */
	debugfs_remove_recursive(serial->debugfs);

	list_del_rcu(&serial->list);
	if (create_loop_dev)
		tty_unregister_device(fwloop_driver,
				      loop_idx(serial->ports[j]));
unregister_ttys:
	for (--j; j >= 0; --j)
		tty_unregister_device(fwtty_driver, serial->ports[j]->index);
	kref_put(&serial->kref, fwserial_destroy);
	return err;

free_ports:
	for (--i; i >= 0; --i) {
		tty_port_destroy(&serial->ports[i]->port);
		kfree(serial->ports[i]);
	}
	kfree(serial);
	return err;
}