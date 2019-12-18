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
struct tty_struct {char* name; int /*<<< orphan*/  flags; struct ser_device* disc_data; int /*<<< orphan*/  receive_room; TYPE_1__* ops; } ;
struct ser_device {int /*<<< orphan*/  node; struct net_device* dev; int /*<<< orphan*/  tty; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int /*<<< orphan*/ * write; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_TTY_CONFIG ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  N_TTY_BUF_SIZE ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caifdev_setup ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_init (struct ser_device*,struct tty_struct*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ser_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  ser_list ; 
 int /*<<< orphan*/  ser_lock ; 
 int /*<<< orphan*/  ser_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_get (struct tty_struct*) ; 
 int /*<<< orphan*/  update_tty_status (struct ser_device*) ; 

__attribute__((used)) static int ldisc_open(struct tty_struct *tty)
{
	struct ser_device *ser;
	struct net_device *dev;
	char name[64];
	int result;

	/* No write no play */
	if (tty->ops->write == NULL)
		return -EOPNOTSUPP;
	if (!capable(CAP_SYS_ADMIN) && !capable(CAP_SYS_TTY_CONFIG))
		return -EPERM;

	/* release devices to avoid name collision */
	ser_release(NULL);

	result = snprintf(name, sizeof(name), "cf%s", tty->name);
	if (result >= IFNAMSIZ)
		return -EINVAL;
	dev = alloc_netdev(sizeof(*ser), name, NET_NAME_UNKNOWN,
			   caifdev_setup);
	if (!dev)
		return -ENOMEM;

	ser = netdev_priv(dev);
	ser->tty = tty_kref_get(tty);
	ser->dev = dev;
	debugfs_init(ser, tty);
	tty->receive_room = N_TTY_BUF_SIZE;
	tty->disc_data = ser;
	set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	rtnl_lock();
	result = register_netdevice(dev);
	if (result) {
		rtnl_unlock();
		free_netdev(dev);
		return -ENODEV;
	}

	spin_lock(&ser_lock);
	list_add(&ser->node, &ser_list);
	spin_unlock(&ser_lock);
	rtnl_unlock();
	netif_stop_queue(dev);
	update_tty_status(ser);
	return 0;
}