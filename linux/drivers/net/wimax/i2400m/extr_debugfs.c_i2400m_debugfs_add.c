#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct dentry* debugfs_dentry; } ;
struct i2400m {int /*<<< orphan*/  trace_msg_from_user; int /*<<< orphan*/  state; int /*<<< orphan*/  tx_out; int /*<<< orphan*/  tx_in; struct dentry* debugfs_dentry; TYPE_1__ wimax_dev; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  d_level_register_debugfs (char*,int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  debugfs ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct i2400m*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_size_t (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver ; 
 int /*<<< orphan*/  fops_i2400m_reset ; 
 int /*<<< orphan*/  fops_i2400m_suspend ; 
 int /*<<< orphan*/  fops_netdev_queue_stopped ; 
 int /*<<< orphan*/  fw ; 
 int /*<<< orphan*/  i2400m_rx_stats_fops ; 
 int /*<<< orphan*/  i2400m_tx_stats_fops ; 
 int /*<<< orphan*/  netdev ; 
 int /*<<< orphan*/  rfkill ; 
 int /*<<< orphan*/  rx ; 
 int /*<<< orphan*/  tx ; 

void i2400m_debugfs_add(struct i2400m *i2400m)
{
	struct dentry *dentry = i2400m->wimax_dev.debugfs_dentry;

	dentry = debugfs_create_dir("i2400m", dentry);
	i2400m->debugfs_dentry = dentry;

	d_level_register_debugfs("dl_", control, dentry);
	d_level_register_debugfs("dl_", driver, dentry);
	d_level_register_debugfs("dl_", debugfs, dentry);
	d_level_register_debugfs("dl_", fw, dentry);
	d_level_register_debugfs("dl_", netdev, dentry);
	d_level_register_debugfs("dl_", rfkill, dentry);
	d_level_register_debugfs("dl_", rx, dentry);
	d_level_register_debugfs("dl_", tx, dentry);

	debugfs_create_size_t("tx_in", 0400, dentry, &i2400m->tx_in);
	debugfs_create_size_t("tx_out", 0400, dentry, &i2400m->tx_out);
	debugfs_create_u32("state", 0600, dentry, &i2400m->state);

	/*
	 * Trace received messages from user space
	 *
	 * In order to tap the bidirectional message stream in the
	 * 'msg' pipe, user space can read from the 'msg' pipe;
	 * however, due to limitations in libnl, we can't know what
	 * the different applications are sending down to the kernel.
	 *
	 * So we have this hack where the driver will echo any message
	 * received on the msg pipe from user space [through a call to
	 * wimax_dev->op_msg_from_user() into
	 * i2400m_op_msg_from_user()] into the 'trace' pipe that this
	 * driver creates.
	 *
	 * So then, reading from both the 'trace' and 'msg' pipes in
	 * user space will provide a full dump of the traffic.
	 *
	 * Write 1 to activate, 0 to clear.
	 *
	 * It is not really very atomic, but it is also not too
	 * critical.
	 */
	debugfs_create_u8("trace_msg_from_user", 0600, dentry,
			  &i2400m->trace_msg_from_user);

	debugfs_create_file("netdev_queue_stopped", 0400, dentry, i2400m,
			    &fops_netdev_queue_stopped);

	debugfs_create_file("rx_stats", 0600, dentry, i2400m,
			    &i2400m_rx_stats_fops);

	debugfs_create_file("tx_stats", 0600, dentry, i2400m,
			    &i2400m_tx_stats_fops);

	debugfs_create_file("suspend", 0200, dentry, i2400m,
			    &fops_i2400m_suspend);

	debugfs_create_file("reset", 0200, dentry, i2400m, &fops_i2400m_reset);
}