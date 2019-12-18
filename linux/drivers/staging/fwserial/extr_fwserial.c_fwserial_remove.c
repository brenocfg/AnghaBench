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
struct fwtty_peer {struct fw_serial* serial; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;
struct fw_serial {int /*<<< orphan*/  kref; int /*<<< orphan*/ * ports; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  list; int /*<<< orphan*/  peer_list; } ;

/* Variables and functions */
 scalar_t__ create_loop_dev ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct fwtty_peer* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwloop_driver ; 
 int /*<<< orphan*/  fwserial_close_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwserial_destroy ; 
 int /*<<< orphan*/  fwserial_list_mutex ; 
 int /*<<< orphan*/  fwserial_remove_peer (struct fwtty_peer*) ; 
 int /*<<< orphan*/  fwtty_driver ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int num_ttys ; 

__attribute__((used)) static void fwserial_remove(struct fw_unit *unit)
{
	struct fwtty_peer *peer = dev_get_drvdata(&unit->device);
	struct fw_serial *serial = peer->serial;
	int i;

	mutex_lock(&fwserial_list_mutex);
	fwserial_remove_peer(peer);

	if (list_empty(&serial->peer_list)) {
		/* unlink from the fwserial_list here */
		list_del_rcu(&serial->list);

		debugfs_remove_recursive(serial->debugfs);

		for (i = 0; i < num_ttys; ++i)
			fwserial_close_port(fwtty_driver, serial->ports[i]);
		if (create_loop_dev)
			fwserial_close_port(fwloop_driver, serial->ports[i]);
		kref_put(&serial->kref, fwserial_destroy);
	}
	mutex_unlock(&fwserial_list_mutex);
}