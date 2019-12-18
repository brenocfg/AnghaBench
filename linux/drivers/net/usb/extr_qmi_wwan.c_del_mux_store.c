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
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {int /*<<< orphan*/  net; int /*<<< orphan*/  data; } ;
struct qmi_wwan_state {int /*<<< orphan*/  flags; } ;
struct net_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  QMI_WWAN_FLAG_MUX ; 
 scalar_t__ kstrtou8 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct usbnet* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 struct net_device* qmimux_find_dev (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmimux_has_slaves (struct usbnet*) ; 
 int /*<<< orphan*/  qmimux_unregister_device (struct net_device*,int /*<<< orphan*/ *) ; 
 int restart_syscall () ; 
 int /*<<< orphan*/  rtnl_trylock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t del_mux_store(struct device *d,  struct device_attribute *attr, const char *buf, size_t len)
{
	struct usbnet *dev = netdev_priv(to_net_dev(d));
	struct qmi_wwan_state *info = (void *)&dev->data;
	struct net_device *del_dev;
	u8 mux_id;
	int ret = 0;

	if (kstrtou8(buf, 0, &mux_id))
		return -EINVAL;

	if (!rtnl_trylock())
		return restart_syscall();

	/* we don't want to modify a running netdev */
	if (netif_running(dev->net)) {
		netdev_err(dev->net, "Cannot change a running device\n");
		ret = -EBUSY;
		goto err;
	}

	del_dev = qmimux_find_dev(dev, mux_id);
	if (!del_dev) {
		netdev_err(dev->net, "mux_id not present\n");
		ret = -EINVAL;
		goto err;
	}
	qmimux_unregister_device(del_dev, NULL);

	if (!qmimux_has_slaves(dev))
		info->flags &= ~QMI_WWAN_FLAG_MUX;
	ret = len;
err:
	rtnl_unlock();
	return ret;
}