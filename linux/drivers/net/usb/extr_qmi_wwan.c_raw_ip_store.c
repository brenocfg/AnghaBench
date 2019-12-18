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
struct usbnet {int /*<<< orphan*/  net; int /*<<< orphan*/  data; } ;
struct qmi_wwan_state {int flags; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  NETDEV_POST_TYPE_CHANGE ; 
 int /*<<< orphan*/  NETDEV_PRE_TYPE_CHANGE ; 
 int QMI_WWAN_FLAG_RAWIP ; 
 int call_netdevice_notifiers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct usbnet* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int notifier_to_errno (int) ; 
 int /*<<< orphan*/  qmi_wwan_netdev_setup (int /*<<< orphan*/ ) ; 
 size_t restart_syscall () ; 
 int /*<<< orphan*/  rtnl_trylock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 scalar_t__ strtobool (char const*,int*) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t raw_ip_store(struct device *d,  struct device_attribute *attr, const char *buf, size_t len)
{
	struct usbnet *dev = netdev_priv(to_net_dev(d));
	struct qmi_wwan_state *info = (void *)&dev->data;
	bool enable;
	int ret;

	if (strtobool(buf, &enable))
		return -EINVAL;

	/* no change? */
	if (enable == (info->flags & QMI_WWAN_FLAG_RAWIP))
		return len;

	if (!rtnl_trylock())
		return restart_syscall();

	/* we don't want to modify a running netdev */
	if (netif_running(dev->net)) {
		netdev_err(dev->net, "Cannot change a running device\n");
		ret = -EBUSY;
		goto err;
	}

	/* let other drivers deny the change */
	ret = call_netdevice_notifiers(NETDEV_PRE_TYPE_CHANGE, dev->net);
	ret = notifier_to_errno(ret);
	if (ret) {
		netdev_err(dev->net, "Type change was refused\n");
		goto err;
	}

	if (enable)
		info->flags |= QMI_WWAN_FLAG_RAWIP;
	else
		info->flags &= ~QMI_WWAN_FLAG_RAWIP;
	qmi_wwan_netdev_setup(dev->net);
	call_netdevice_notifiers(NETDEV_POST_TYPE_CHANGE, dev->net);
	ret = len;
err:
	rtnl_unlock();
	return ret;
}